#ifndef __KFAIMPORTER_H__
#define __KFAIMPORTER_H__

#include "BaseImporter.h"
#include "IniSection.h"
#include <obj/NiKeyframeController.h>
#include <obj/NiKeyframeData.h>
#include "../NifProps/iNifProps.h"

// KFA Importer
class KFAImporter : public BaseImporter, IFileResolver//, public IniFileSection
{
public:
	// Ini settings
	bool autoDetect;

	bool clearAnimation;
	tstring animnodesFile;

	int unnamedCounter;

	vector<Niflib::NiObjectRef> blocks;
	vector<Niflib::NiNodeRef> nodes;

	KFAImporter(const TCHAR *Name, ImpInterface *I, Interface *GI, BOOL SuppressPrompts);
	virtual void Initialize();
	virtual void ReadBlocks();
	void BuildNodes();
	void BuildNodes(Niflib::NiNodeRef object, vector<Niflib::NiNodeRef>& nodes);

	// Ini File related routines
	virtual void LoadIniSettings();
	virtual void SaveIniSettings();

	void ApplyAppSettings(bool initialize = false);

	bool FindFile(const tstring& name, tstring& resolved_name) const override;
	bool FindFileByType(const tstring& name, FileType type, tstring& resolved_name) const override;
	bool GetRelativePath(tstring& name, FileType type) const override;

	bool ShowDialog();
	virtual bool DoImport();

	// Animation Helpers
	void ApplyBoneValues( INode* pNode, const std::map< std::wstring, NiKeyframeControllerRef >& animNodes );
	bool ImportAnimation();
	void ClearAnimation();
	void ClearAnimation(INode *node);

	bool AddValues( Control *c, NiKeyframeDataRef data, float time );

	Control* MakePosition( Control *tmCont, Class_ID clsid );
	Control* MakePositionXYZ( Control *tmCont, Class_ID clsid );
	Control* MakeRotation( Control *tmCont, Class_ID rotClsid, Class_ID rollClsid );
	Control* MakeScale( Control *tmCont, Class_ID clsid );
	Control* MakeFloat( IParamBlock* pblock, int idx, Class_ID clsid );

protected:
	KFAImporter();
};

#endif
