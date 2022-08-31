#include "stdafx.h"
#include "MaxNifImport.h"
#include "KFAImporter.h"

#include <IFrameTagManager.h>

using namespace Niflib;

// Define the standard section names used in the ini file
extern LPCTSTR NifImportSection;
extern LPCTSTR AnimImportSection;

const Class_ID IPOS_CONTROL_CLASS_ID = Class_ID( 0x118f7e02, 0xffee238a );
enum
{
	IPOS_X_REF = 0,
	IPOS_Y_REF = 1,
	IPOS_Z_REF = 2,
	IPOS_W_REF = 3,
};

KFAImporter::KFAImporter(const TCHAR *Name, ImpInterface *I, Interface *GI, BOOL SuppressPrompts)
	: BaseImporter()
{
	BaseInit(Name, I, GI, SuppressPrompts);
}

KFAImporter::KFAImporter()
{
}

void KFAImporter::ReadBlocks()
{
	Niflib::NifInfo info;
	blocks = ReadNifList(T2AString(name), &info);
	root = SelectFirstObjectOfType<NiObject>(blocks);
	nifVersion = info.version;
	userVersion = info.userVersion;
	userVersion2 = info.userVersion2;
	this->unnamedCounter = 0;
	BuildNodes();
}


void KFAImporter::BuildNodes(NiNodeRef object, vector<NiNodeRef>& nodes)
{
	if (!object)
		return;

	// Handle nodes without names by setting before importing.  Really a hack but so is editing in nifskope and not settings names
	string name = object->GetName();
	if (name.empty())
	{
		name = FormatString("noname:%d", ++unnamedCounter);
		object->SetName(name);
	}
	nodes.push_back(object);
	vector<NiNodeRef> links = DynamicCast<NiNode>(object->GetChildren());
	for (vector<NiNodeRef>::iterator itr = links.begin(), end = links.end(); itr != end; ++itr)
		BuildNodes(*itr, nodes);
}

void KFAImporter::BuildNodes()
{
	BuildNodes(root, nodes);
	std::sort(nodes.begin(), nodes.end(), NodeEquivalence());
}

void KFAImporter::Initialize()
{
}

void KFAImporter::LoadIniSettings()
{
	TCHAR iniName[MAX_PATH];
	GetIniFileName(iniName);
	this->iniFileName = iniName;
	iniFileValid = (-1 != _taccess(iniName, 0));

	// Locate which application to use. If Auto, find first app where this file appears in the root path list
	appSettings = nullptr;
	tstring curapp = GetIniValue<tstring>(NifImportSection, TEXT("CurrentApp"), TEXT("AUTO"));
	tstring lastselapp = GetIniValue<tstring>(NifImportSection, TEXT("LastSelectedApp"), TEXT(""));
	if (0 == _tcsicmp(curapp.c_str(), TEXT("AUTO"))) {
		autoDetect = true;
		// Scan Root paths
		bool versionmatch = false;
		int version = GetNifVersion(T2AString(this->name));
		for (AppSettingsMap::iterator itr = TheAppSettings.begin(), end = TheAppSettings.end(); itr != end; ++itr) {
			if ((*itr).IsFileInRootPaths(this->name)) {
				appSettings = &(*itr);
				break;
			}
			else if (!versionmatch && ParseVersionString(T2AString((*itr).NiVersion)) == version) {
				// Version matching is an ok fit but we want the other if possible. And we want the first match if possible.
				appSettings = &(*itr);
				versionmatch = true;
			}
		}
	}
	else {
		autoDetect = false;
		appSettings = FindAppSetting(curapp);
	}
	if (appSettings == nullptr && !lastselapp.empty())
		appSettings = FindAppSetting(lastselapp);
	if (appSettings == nullptr && !TheAppSettings.empty()) {
		appSettings = &TheAppSettings.front();
	}

	clearAnimation = GetIniValue( AnimImportSection, TEXT( "ClearAnimation" ), true );
	animnodesFile = GetIniValue<tstring>( AnimImportSection, TEXT( "AnimNodes" ), TEXT( "animnodes.dat" ) );

	ApplyAppSettings(true);
}
void KFAImporter::ApplyAppSettings(bool initialize)
{
}

void KFAImporter::SaveIniSettings()
{
	SetIniValue( AnimImportSection, TEXT( "ClearAnimation" ), clearAnimation );
	SetIniValue( AnimImportSection, TEXT( "AnimNodes" ), animnodesFile );

	SetIniValue<tstring>(NifImportSection, TEXT("CurrentApp"), autoDetect ? TEXT("AUTO") : appSettings->Name);
	SetIniValue<tstring>(NifImportSection, TEXT("LastSelectedApp"), appSettings->Name);
}

bool KFAImporter::FindFile(const tstring& name, tstring& resolved_name) const
{
	TCHAR buffer[MAX_PATH];

	// Simply check for fully qualified path
	if (!PathIsRelative(name.c_str())) {
		if (-1 != _taccess(name.c_str(), 0)) {
			resolved_name = tstring(name);
			return true;
		}
	}
	if (!path.empty()) {
		PathCombine(buffer, path.c_str(), name.c_str()); // try as-is
		if (-1 != _taccess(buffer, 0)) {
			resolved_name = tstring(buffer);
			return true;
		}

		// try only filename in nif directory
		PathCombine(buffer, path.c_str(), PathFindFileName(name.c_str()));
		if (-1 != _taccess(buffer, 0)) {
			resolved_name = tstring(buffer);
			return true;
		}
	}
	if (appSettings != nullptr) {
		return appSettings->FindFile(name, resolved_name);
	}
	resolved_name = name;
	return false;
}

bool KFAImporter::FindFileByType(const tstring& name, FileType type, tstring& resolved_name) const
{
	return FindFile(name, resolved_name);
}

bool KFAImporter::GetRelativePath(tstring& name, FileType type) const
{
	if (type == FT_Texture) {
		if (appSettings != nullptr) {
			name = appSettings->GetRelativeTexPath(name, TEXT("textures"));
			return true;
		}
	}
	return false;
}

bool KFAImporter::DoImport()
{
	bool ok = true;
	if (!suppressPrompts)
	{
		if (!ShowDialog())
			return true;

		ApplyAppSettings(false);
		SaveIniSettings();
	}

	unnamedCounter = 0;

	ClearAnimation();
	return ImportAnimation();
}

static void ClearAnimation( Control *c )
{
	if( c != nullptr )
	{
		if( c->IsColorController() )
			return;

		if( IKeyControl *ikeys = GetKeyControlInterface( c ) )
		{
			ikeys->SetNumKeys( 0 );
		}
#if VERSION_3DSMAX > ((5000<<16)+(15<<8)+0) // Version 5
		if( Control *sc = c->GetWController() )
		{
			if( sc != c ) ClearAnimation( sc );
		}
#endif
		if( Control *sc = c->GetXController() )
		{
			if( sc != c ) ClearAnimation( sc );
		}
		if( Control *sc = c->GetYController() )
		{
			if( sc != c ) ClearAnimation( sc );
		}
		if( Control *sc = c->GetZController() )
		{
			if( sc != c ) ClearAnimation( sc );
		}
		if( Control *sc = c->GetRotationController() )
		{
			if( sc != c ) ClearAnimation( sc );
		}
		if( Control *sc = c->GetPositionController() )
		{
			if( sc != c ) ClearAnimation( sc );
		}
		if( Control *sc = c->GetScaleController() )
		{
			if( sc != c ) ClearAnimation( sc );
		}
	}
}

void KFAImporter::ClearAnimation( INode *node )
{
	if( node != nullptr )
	{
		if( node->HasNoteTracks() )
		{
			for( int i = node->NumNoteTracks() - 1; i >= 0; --i )
			{
				if( NoteTrack *nt = node->GetNoteTrack( i ) )
					node->DeleteNoteTrack( nt, TRUE );
			}
		}
		node->DeleteKeys( TRACK_DOALL );
		::ClearAnimation( node->GetTMController() );
		for( int i = 0, n = node->NumberOfChildren(); i < n; ++i )
		{
			ClearAnimation( node->GetChildNode( i ) );
		}

		// Clear animation priority
		if( node->UserPropExists( NP_ANM_PRI ) )
		{
			node->SetUserPropString( NP_ANM_PRI, TEXT( "" ) );
		}
	}
}
void KFAImporter::ClearAnimation()
{
	if( clearAnimation )
	{
#if VERSION_3DSMAX >= ((7000<<16)+(15<<8)+0) // Version 7
		if( IFrameTagManager *tagMgr = (IFrameTagManager*)GetCOREInterface( FRAMETAGMANAGER_INTERFACE ) )
		{
			int n = tagMgr->GetTagCount();
			for( int i = n - 1; i >= 0; --i )
			{
				tagMgr->DeleteTag( tagMgr->GetTagID( i ) );
			}
		}
#endif
		ClearAnimation( gi->GetRootNode() );
	}
}


void KFAImporter::ApplyBoneValues( INode* pNode, const std::map< std::wstring, NiKeyframeControllerRef >& animNodes )
{
	const std::wstring nodeName = pNode->GetName();
	const std::map< std::wstring, NiKeyframeControllerRef >::const_iterator it = animNodes.find( nodeName );
	if( it != animNodes.end() )
	{
		const NiKeyframeDataRef keyframeData = it->second->GetData();
		if( keyframeData )
		{
			AddValues( pNode->GetTMController(), keyframeData, 0.0f );
		}
		else
		{
			pNode->GetName();
		}
	}

	for( int i = 0u; i < pNode->NumberOfChildren(); ++i )
	{
		INode* pChildNode = pNode->GetChildNode( i );
		ApplyBoneValues( pChildNode, animNodes );
	}
}

bool KFAImporter::ImportAnimation()
{
	std::map< size_t, std::wstring > animNodeIndices;
	{
		std::wifstream file( animnodesFile, ifstream::in );

		std::wstring line;
		while( std::getline( file, line ) )
		{
			const size_t index = animNodeIndices.size();
			animNodeIndices[ index ] = line;
		}
	}

	INode* pRootNode = gi->GetRootNode();
	if( pRootNode == nullptr )
	{
		return false;
	}

	NiAVObjectRef rootAV = DynamicCast<NiAVObject>( root );
	if( !rootAV )
	{
		return false;
	}

	std::list< NiExtraDataRef > extraDatas = rootAV->GetExtraData();
	std::list< NiTimeControllerRef > controllers = rootAV->GetControllers();
	if( extraDatas.size() != controllers.size() )
	{
		return false;
	}

	std::map< std::wstring, NiKeyframeControllerRef > animNodes;

	std::list< NiExtraDataRef >::iterator extraDataIterator = extraDatas.begin();
	std::list< NiTimeControllerRef >::iterator controllerIterator = controllers.begin();
	for( ; extraDataIterator != extraDatas.end() && controllerIterator != controllers.end(); ++extraDataIterator, ++controllerIterator )
	{
		const NiStringExtraDataRef extraData = DynamicCast< NiStringExtraData >( *extraDataIterator );
		if( !extraData )
		{
			continue;
		}

		const size_t index = (size_t)std::stoi( extraData->GetData() );
		const std::map< size_t, std::wstring >::const_iterator it = animNodeIndices.find( index );
		if( it != animNodeIndices.end() )
		{
			const NiKeyframeControllerRef keyframeController = DynamicCast< NiKeyframeController >( *controllerIterator );
			if( !keyframeController )
			{
				continue;
			}

			animNodes[ it->second ] = keyframeController;
		}
	}

	ApplyBoneValues( pRootNode, animNodes );
}

bool KFAImporter::AddValues( Control *c, NiKeyframeDataRef data, float time )
{
	vector<Vector3Key> posKeys = data->GetTranslateKeys();
	vector<QuatKey> quatKeys = data->GetQuatRotateKeys();
	vector<FloatKey> sclKeys = data->GetScaleKeys();
	vector<FloatKey> xKeys = data->GetXRotateKeys();
	vector<FloatKey> yKeys = data->GetYRotateKeys();
	vector<FloatKey> zKeys = data->GetZRotateKeys();

	// Require more than one key to import (to avoid zero frame positioning used in mw and daoc
	if( !(posKeys.size() > 1
			|| quatKeys.size() > 1
			|| sclKeys.size() > 1
			|| xKeys.size() > 1
			|| yKeys.size() > 1
			|| zKeys.size() > 1
			) )
	{
		return false;
	}

	// Handle Translation
	switch( data->GetTranslateType() )
	{
	case LINEAR_KEY:
		if( Control *subCtrl = MakePositionXYZ( c, Class_ID( LININTERP_FLOAT_CLASS_ID, 0 ) ) )
		{
			vector<FloatKey> xkeys, ykeys, zkeys;
			SplitKeys( posKeys, xkeys, ykeys, zkeys );
			MergeKeys<ILinFloatKey, FloatKey>( subCtrl->GetXController(), xkeys, time );
			MergeKeys<ILinFloatKey, FloatKey>( subCtrl->GetYController(), ykeys, time );
			MergeKeys<ILinFloatKey, FloatKey>( subCtrl->GetZController(), zkeys, time );
		}
		break;

	case QUADRATIC_KEY:
	case XYZ_ROTATION_KEY:
		if( Control *subCtrl = MakePositionXYZ( c, Class_ID( HYBRIDINTERP_FLOAT_CLASS_ID, 0 ) ) )
		{
			vector<FloatKey> xkeys, ykeys, zkeys;
			SplitKeys( posKeys, xkeys, ykeys, zkeys );
			MergeKeys<IBezFloatKey, FloatKey>( subCtrl->GetXController(), xkeys, time );
			MergeKeys<IBezFloatKey, FloatKey>( subCtrl->GetYController(), ykeys, time );
			MergeKeys<IBezFloatKey, FloatKey>( subCtrl->GetZController(), zkeys, time );
		}
		break;

	case TBC_KEY:
		if( Control *subCtrl = MakePositionXYZ( c, Class_ID( TCBINTERP_FLOAT_CLASS_ID, 0 ) ) )
		{
			vector<FloatKey> xkeys, ykeys, zkeys;
			SplitKeys( posKeys, xkeys, ykeys, zkeys );
			MergeKeys<ITCBFloatKey, FloatKey>( subCtrl->GetXController(), xkeys, time );
			MergeKeys<ITCBFloatKey, FloatKey>( subCtrl->GetYController(), ykeys, time );
			MergeKeys<ITCBFloatKey, FloatKey>( subCtrl->GetZController(), zkeys, time );
		}
		break;
	}

	// Handle Rotation
	switch( data->GetRotateType() )
	{
	case LINEAR_KEY:
		if( Control *subCtrl = MakeRotation( c, Class_ID( LININTERP_ROTATION_CLASS_ID, 0 ), Class_ID( LININTERP_FLOAT_CLASS_ID, 0 ) ) )
		{
			MergeKeys<ILinRotKey, QuatKey>( subCtrl, quatKeys, time );
		}
		break;

	case QUADRATIC_KEY:
		if( Control *subCtrl = MakeRotation( c, Class_ID( HYBRIDINTERP_ROTATION_CLASS_ID, 0 ), Class_ID( HYBRIDINTERP_FLOAT_CLASS_ID, 0 ) ) )
		{
			MergeKeys<IBezQuatKey, QuatKey>( subCtrl, quatKeys, time );
		}
		break;

	case XYZ_ROTATION_KEY:
		if( Control *subCtrl = MakeRotation( c, Class_ID( EULER_CONTROL_CLASS_ID, 0 ), Class_ID( HYBRIDINTERP_FLOAT_CLASS_ID, 0 ) ) )
		{
			MergeKeys<IBezFloatKey, FloatKey>( subCtrl->GetXController(), xKeys, time );
			MergeKeys<IBezFloatKey, FloatKey>( subCtrl->GetYController(), yKeys, time );
			MergeKeys<IBezFloatKey, FloatKey>( subCtrl->GetZController(), zKeys, time );
		}
		break;

	case TBC_KEY:
		if( Control *subCtrl = MakeRotation( c, Class_ID( TCBINTERP_ROTATION_CLASS_ID, 0 ), Class_ID( TCBINTERP_FLOAT_CLASS_ID, 0 ) ) )
		{
			MergeKeys<ITCBRotKey, QuatKey>( subCtrl, quatKeys, time );
		}
		break;
	}
	// Handle Scale
	switch( data->GetScaleType() )
	{
	case LINEAR_KEY:
		if( Control *subCtrl = MakeScale( c, Class_ID( LININTERP_SCALE_CLASS_ID, 0 ) ) )
		{
			MergeKeys<ILinScaleKey, FloatKey>( subCtrl, sclKeys, time );
		}
		break;
	case QUADRATIC_KEY:
	case XYZ_ROTATION_KEY:
		if( Control *subCtrl = MakeScale( c, Class_ID( HYBRIDINTERP_SCALE_CLASS_ID, 0 ) ) )
		{
			MergeKeys<IBezScaleKey, FloatKey>( subCtrl, sclKeys, time );
		}
		break;
	case TBC_KEY:
		if( Control *subCtrl = MakeScale( c, Class_ID( TCBINTERP_SCALE_CLASS_ID, 0 ) ) )
		{
			MergeKeys<ITCBScaleKey, FloatKey>( subCtrl, sclKeys, time );
		}
		break;
	}
	return true;
}


Control* KFAImporter::MakeRotation( Control *tmCont, Class_ID rotClsid, Class_ID rollClsid )
{
	Interface *ip = gi;
	if( Control *c = tmCont->GetRotationController() )
	{
		if( c->ClassID() != rotClsid )
		{
			if( Control *tmpCtrl = (Control*)ip->CreateInstance( CTRL_ROTATION_CLASS_ID, rotClsid ) )
			{
				if( !tmCont->SetRotationController( tmpCtrl ) )
					tmpCtrl->DeleteThis();
				else
					c = tmpCtrl;
			}
		}
		if( Control *r = tmCont->GetRollController() )
		{
			if( r->ClassID() != rollClsid )
			{
				if( Control *r = (Control*)ip->CreateInstance( CTRL_FLOAT_CLASS_ID, rollClsid ) )
					if( !tmCont->SetRollController( r ) )
						r->DeleteThis();
			}
		}
		return c;
	}
	return nullptr;
}

Control* KFAImporter::MakeScale( Control *tmCont, Class_ID clsid )
{
	Interface *ip = gi;
	if( Control *c = tmCont->GetScaleController() )
	{
		if( c->ClassID() != clsid )
		{
			if( Control *tmpCtrl = (Control*)ip->CreateInstance( CTRL_SCALE_CLASS_ID, clsid ) )
			{
				if( !tmCont->SetScaleController( tmpCtrl ) )
					tmpCtrl->DeleteThis();
				else
					c = tmpCtrl;
			}
		}
		return c;
	}
	return nullptr;
}
Control* KFAImporter::MakeFloat( IParamBlock* pblock, int idx, Class_ID clsid )
{
	Interface *ip = gi;
	if( Control *c = pblock->GetController( idx ) )
	{
		if( c->ClassID() != clsid )
		{
			if( Control *tmpCtrl = (Control*)ip->CreateInstance( CTRL_SCALE_CLASS_ID, clsid ) )
			{
				pblock->SetController( idx, tmpCtrl );
				if( pblock->GetController( idx ) != tmpCtrl )
					tmpCtrl->DeleteThis();
				else
					c = tmpCtrl;
			}
		}
		return c;
	}
	return nullptr;
}

Control* KFAImporter::MakePosition( Control *tmCont, Class_ID clsid )
{
	Interface *ip = gi;
	if( Control *c = tmCont->GetPositionController() )
	{
		if( c->ClassID() != clsid )
		{
			if( Control *tmpCtrl = (Control*)ip->CreateInstance( CTRL_POSITION_CLASS_ID, clsid ) )
			{
				if( !tmCont->SetPositionController( tmpCtrl ) )
					tmpCtrl->DeleteThis();
				else
					c = tmpCtrl;
			}
		}
		return c;
	}
	return nullptr;
}

Control* KFAImporter::MakePositionXYZ( Control *tmCont, Class_ID clsid )
{
	Interface *ip = gi;
	// First make the controller and XYZ Independent position controller, then fix individuals
	if( Control *c = MakePosition( tmCont, IPOS_CONTROL_CLASS_ID ) )
	{
		if( Control *x = c->GetXController() )
		{
			if( x->ClassID() != clsid )
			{
				if( Control *tmp = (Control*)ip->CreateInstance( CTRL_FLOAT_CLASS_ID, clsid ) )
					c->ReplaceReference( IPOS_X_REF, tmp );
			}
		}
		if( Control *y = c->GetYController() )
		{
			if( y->ClassID() != clsid )
			{
				if( Control *tmp = (Control*)ip->CreateInstance( CTRL_FLOAT_CLASS_ID, clsid ) )
					c->ReplaceReference( IPOS_Y_REF, tmp );
			}
		}
		if( Control *z = c->GetZController() )
		{
			if( z->ClassID() != clsid )
			{
				if( Control *tmp = (Control*)ip->CreateInstance( CTRL_FLOAT_CLASS_ID, clsid ) )
					c->ReplaceReference( IPOS_Z_REF, tmp );
			}
		}
		return c;
	}
	return nullptr;
}