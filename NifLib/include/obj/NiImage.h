/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _NIIMAGE_H_
#define _NIIMAGE_H_

//--BEGIN FILE HEAD CUSTOM CODE--//
//--END CUSTOM CODE--//

#include "NiObject.h"

// Include structures
#include "../Ref.h"
namespace Niflib {

// Forward define of referenced NIF objects
class NiRawImageData;
class NiImage;
typedef Ref<NiImage> NiImageRef;

/*!  */
class NiImage : public NiObject {
public:
	/*! Constructor */
	NIFLIB_API NiImage();

	/*! Destructor */
	NIFLIB_API virtual ~NiImage();

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

	// 0 if the texture is internal to the NIF file.
	// \return The current value.
	byte GetUseExternal() const;

	// 0 if the texture is internal to the NIF file.
	// \param[in] value The new value.
	void SetUseExternal( byte value );

	// The filepath to the texture.
	// \return The current value.
	IndexString GetFileName() const;

	// The filepath to the texture.
	// \param[in] value The new value.
	void SetFileName( const IndexString & value );

	// Link to the internally stored image data.
	// \return The current value.
	Ref<NiRawImageData > GetImageData() const;

	// Link to the internally stored image data.
	// \param[in] value The new value.
	void SetImageData( Ref<NiRawImageData > value );

	****End Example Naive Implementation***/

	//--BEGIN MISC CUSTOM CODE--//

	/*!
	 * Used to check whether the texture referenced by this object is an external file.
	 * \return True if the texture is stored in an external file, false if it is stored within this NIF file.
	 */
	NIFLIB_API bool IsTextureExternal() const;

	/*!
	 * Sets a new external file texture.  Removes any existing texture references, whether internal or external.
	 * \param[in] file_name The file name of the external texture.  Often needs to follow game guidlines to be found.
	 */
	NIFLIB_API void SetExternalTexture( string file_name );

	/*!
	 * Sets a new internal file texture.  Removes any existing texture references, whether internal or external.
	 * \param[in] raw_image_data The NiRawImageData object that contains the texture image data.
	 */
	NIFLIB_API void SetInternalTexture( NiRawImageData * raw_image_data );


	/*!
	 * Returns either the file name of the external texture, or the original file name of the internal one.
	 * \return The name of the texture file.
	 */
	NIFLIB_API string GetTextureFileName() const;

	/*!
	 * Returns a reference to the texture image data object used by this texture, if any.
	 * \return The iamge data object referenced by this texture, or NULL if one is not being used.
	 */
	NIFLIB_API Ref<NiRawImageData> GetRawImageData() const;


	//--END CUSTOM CODE--//
protected:
	/*! 0 if the texture is internal to the NIF file. */
	byte useExternal;
	/*! The filepath to the texture. */
	IndexString fileName;
	/*! Link to the internally stored image data. */
	Ref<NiRawImageData > imageData;
	/*! Unknown.  Often seems to be 7. Perhaps m_uiMipLevels? */
	unsigned int unknownInt;
	/*! Unknown.  Perhaps fImageScale? */
	float unknownFloat;
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