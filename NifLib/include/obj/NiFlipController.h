/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _NIFLIPCONTROLLER_H_
#define _NIFLIPCONTROLLER_H_

//--BEGIN FILE HEAD CUSTOM CODE--//
//--END CUSTOM CODE--//

#include "NiFloatInterpController.h"

// Include structures
#include "../Ref.h"
namespace Niflib {

// Forward define of referenced NIF objects
class NiSourceTexture;
class NiImage;
class NiFlipController;
typedef Ref<NiFlipController> NiFlipControllerRef;

/*! Texture flipping controller. */
class NiFlipController : public NiFloatInterpController {
public:
	/*! Constructor */
	NIFLIB_API NiFlipController();

	/*! Destructor */
	NIFLIB_API virtual ~NiFlipController();

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

	// Target texture slot (0=base, 4=glow).
	// \return The current value.
	TexType GetTextureSlot() const;

	// Target texture slot (0=base, 4=glow).
	// \param[in] value The new value.
	void SetTextureSlot( const TexType & value );

	// Time between two flips.
	//             delta = (start_time - stop_time) / sources.num_indices
	// \return The current value.
	float GetDelta() const;

	// Time between two flips.
	//             delta = (start_time - stop_time) / sources.num_indices
	// \param[in] value The new value.
	void SetDelta( float value );

	// The texture sources.
	// \return The current value.
	vector<Ref<NiSourceTexture > > GetSources() const;

	// The texture sources.
	// \param[in] value The new value.
	void SetSources( const vector<Ref<NiSourceTexture > >& value );

	// The image sources
	// \return The current value.
	vector<Ref<NiImage > > GetImages() const;

	// The image sources
	// \param[in] value The new value.
	void SetImages( const vector<Ref<NiImage > >& value );

	****End Example Naive Implementation***/

	//--BEGIN MISC CUSTOM CODE--//
	//--END CUSTOM CODE--//
protected:
	/*! Target texture slot (0=base, 4=glow). */
	TexType textureSlot;
	/*! 0? */
	unsigned int unknownInt2;
	/*!
	 * Time between two flips.
	 *             delta = (start_time - stop_time) / sources.num_indices
	 */
	float delta;
	/*! The number of source objects. */
	mutable unsigned int numSources;
	/*! The texture sources. */
	vector<Ref<NiSourceTexture > > sources;
	/*! The image sources */
	vector<Ref<NiImage > > images;
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