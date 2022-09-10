/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _BSSHADERTEXTURESET_H_
#define _BSSHADERTEXTURESET_H_

//--BEGIN FILE HEAD CUSTOM CODE--//

//--END CUSTOM CODE--//

#include "NiObject.h"
namespace Niflib {

class BSShaderTextureSet;
typedef Ref<BSShaderTextureSet> BSShaderTextureSetRef;

/*! Bethesda-specific Texture Set. */
class BSShaderTextureSet : public NiObject {
public:
	/*! Constructor */
	NIFLIB_API BSShaderTextureSet();

	/*! Destructor */
	NIFLIB_API virtual ~BSShaderTextureSet();

	/*!
	 * A constant value which uniquly identifies objects of this type.
	 */
	NIFLIB_API static const Type TYPE;

	/*!
	 * A factory function used during file reading to create an instance of this type of object.
	 * \return A pointer to a newly allocated instance of this type of object.
	 */
	NIFLIB_API static NiObject * Create();

	/*!
	 * Summarizes the information contained in this object in English.
	 * \param[in] verbose Determines whether or not detailed information about large areas of data will be printed out.
	 * \return A string containing a summary of the information within the object in English.  This is the function that Niflyze calls to generate its analysis, so the output is the same.
	 */
	NIFLIB_API virtual string asString( bool verbose = false ) const;

	/*!
	 * Used to determine the type of a particular instance of this object.
	 * \return The type constant for the actual type of the object.
	 */
	NIFLIB_API virtual const Type & GetType() const;

	/***Begin Example Naive Implementation****

	// Textures.
	//             0: Diffuse
	//             1: Normal/Gloss
	//             2: Glow(SLSF2_Glow_Map)/Skin/Hair/Rim light(SLSF2_Rim_Lighting)
	//             3: Height/Parallax
	//             4: Environment
	//             5: Environment Mask
	//             6: Subsurface for Multilayer Parallax
	//             7: Back Lighting Map (SLSF2_Back_Lighting)
	// \return The current value.
	vector<string > GetTextures() const;

	// Textures.
	//             0: Diffuse
	//             1: Normal/Gloss
	//             2: Glow(SLSF2_Glow_Map)/Skin/Hair/Rim light(SLSF2_Rim_Lighting)
	//             3: Height/Parallax
	//             4: Environment
	//             5: Environment Mask
	//             6: Subsurface for Multilayer Parallax
	//             7: Back Lighting Map (SLSF2_Back_Lighting)
	// \param[in] value The new value.
	void SetTextures( const vector<string >& value );

	****End Example Naive Implementation***/

	//--BEGIN MISC CUSTOM CODE--//

	// Textures
	// \return The current value.
	vector<string > GetTextures() const;

	// Textures
	// \param[in] value The new value.
	void SetTextures( const vector<string >& value );

	// Textures
	// \return The current value.
	string GetTexture( size_t i ) const;

	// Textures
	// \param[in] i Index of texture to set
	// \param[in] value The new value.
	void SetTexture( size_t i, const string& value);

	//--END CUSTOM CODE--//
protected:
	/*! Number of Textures */
	mutable int numTextures;
	/*!
	 * Textures.
	 *             0: Diffuse
	 *             1: Normal/Gloss
	 *             2: Glow(SLSF2_Glow_Map)/Skin/Hair/Rim light(SLSF2_Rim_Lighting)
	 *             3: Height/Parallax
	 *             4: Environment
	 *             5: Environment Mask
	 *             6: Subsurface for Multilayer Parallax
	 *             7: Back Lighting Map (SLSF2_Back_Lighting)
	 */
	vector<string > textures;
public:
	/*! NIFLIB_HIDDEN function.  For internal use only. */
	NIFLIB_HIDDEN virtual void Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info );
	/*! NIFLIB_HIDDEN function.  For internal use only. */
	NIFLIB_HIDDEN virtual void Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const;
	/*! NIFLIB_HIDDEN function.  For internal use only. */
	NIFLIB_HIDDEN virtual void FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info );
	/*! NIFLIB_HIDDEN function.  For internal use only. */
	NIFLIB_HIDDEN virtual list<NiObjectRef> GetRefs() const;
	/*! NIFLIB_HIDDEN function.  For internal use only. */
	NIFLIB_HIDDEN virtual list<NiObject *> GetPtrs() const;
};

//--BEGIN FILE FOOT CUSTOM CODE--//

//--END CUSTOM CODE--//

} //End Niflib namespace
#endif