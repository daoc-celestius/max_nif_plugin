/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _BSPROCEDURALLIGHTNINGCONTROLLER_H_
#define _BSPROCEDURALLIGHTNINGCONTROLLER_H_

//--BEGIN FILE HEAD CUSTOM CODE--//

//--END CUSTOM CODE--//

#include "NiFloatInterpController.h"

// Include structures
#include "../Ref.h"
namespace Niflib {

// Forward define of referenced NIF objects
class NiInterpolator;
class NiObject;
class BSProceduralLightningController;
typedef Ref<BSProceduralLightningController> BSProceduralLightningControllerRef;

/*!
 * Skyrim, Paired with dummy TriShapes, this controller generates lightning shapes
 * for special effects.
 *     First interpolator controls Generation.
 */
class BSProceduralLightningController : public NiFloatInterpController {
public:
	/*! Constructor */
	NIFLIB_API BSProceduralLightningController();

	/*! Destructor */
	NIFLIB_API virtual ~BSProceduralLightningController();

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

	// References interpolator for Mutation of strips
	// \return The current value.
	Ref<NiInterpolator > GetInterpolator2_Mutation() const;

	// References interpolator for Mutation of strips
	// \param[in] value The new value.
	void SetInterpolator2_Mutation( Ref<NiInterpolator > value );

	// Unknown
	// \return The current value.
	Ref<NiInterpolator > GetInterpolator3() const;

	// Unknown
	// \param[in] value The new value.
	void SetInterpolator3( Ref<NiInterpolator > value );

	// Unknown
	// \return The current value.
	Ref<NiInterpolator > GetInterpolator4() const;

	// Unknown
	// \param[in] value The new value.
	void SetInterpolator4( Ref<NiInterpolator > value );

	// Unknown
	// \return The current value.
	Ref<NiInterpolator > GetInterpolator5() const;

	// Unknown
	// \param[in] value The new value.
	void SetInterpolator5( Ref<NiInterpolator > value );

	// Unknown
	// \return The current value.
	Ref<NiInterpolator > GetInterpolator6() const;

	// Unknown
	// \param[in] value The new value.
	void SetInterpolator6( Ref<NiInterpolator > value );

	// Unknown
	// \return The current value.
	Ref<NiInterpolator > GetInterpolator7() const;

	// Unknown
	// \param[in] value The new value.
	void SetInterpolator7( Ref<NiInterpolator > value );

	// Unknown
	// \return The current value.
	Ref<NiInterpolator > GetInterpolator8() const;

	// Unknown
	// \param[in] value The new value.
	void SetInterpolator8( Ref<NiInterpolator > value );

	// References interpolator for Amplitutde control. 0=straight, 50=wide
	// \return The current value.
	Ref<NiInterpolator > GetInterpolator9_ArcOffset() const;

	// References interpolator for Amplitutde control. 0=straight, 50=wide
	// \param[in] value The new value.
	void SetInterpolator9_ArcOffset( Ref<NiInterpolator > value );

	// How far lightning will stretch to.
	// \return The current value.
	float GetDistanceWeight() const;

	// How far lightning will stretch to.
	// \param[in] value The new value.
	void SetDistanceWeight( float value );

	// Unknown
	// \return The current value.
	float GetFloat2() const;

	// Unknown
	// \param[in] value The new value.
	void SetFloat2( float value );

	// How wide the bolt will be
	// \return The current value.
	float GetStripWidth() const;

	// How wide the bolt will be
	// \param[in] value The new value.
	void SetStripWidth( float value );

	// Influences forking behavior
	// \return The current value.
	float GetFork() const;

	// Influences forking behavior
	// \param[in] value The new value.
	void SetFork( float value );

	// Unknown
	// \return The current value.
	float GetFloat5() const;

	// Unknown
	// \param[in] value The new value.
	void SetFloat5( float value );

	// Unknown
	// \return The current value.
	byte GetByte1() const;

	// Unknown
	// \param[in] value The new value.
	void SetByte1( byte value );

	// Unknown
	// \return The current value.
	byte GetByte2() const;

	// Unknown
	// \param[in] value The new value.
	void SetByte2( byte value );

	// Unknown
	// \return The current value.
	byte GetByte3() const;

	// Unknown
	// \param[in] value The new value.
	void SetByte3( byte value );

	// Unknown, unsure if this is actually another interpolator link.
	// \return The current value.
	Ref<NiObject > GetInterpolator10_() const;

	// Unknown, unsure if this is actually another interpolator link.
	// \param[in] value The new value.
	void SetInterpolator10_( Ref<NiObject > value );

	****End Example Naive Implementation***/

	//--BEGIN MISC CUSTOM CODE--//

	//--END CUSTOM CODE--//
protected:
	/*! References interpolator for Mutation of strips */
	Ref<NiInterpolator > interpolator2_Mutation;
	/*! Unknown */
	Ref<NiInterpolator > interpolator3;
	/*! Unknown */
	Ref<NiInterpolator > interpolator4;
	/*! Unknown */
	Ref<NiInterpolator > interpolator5;
	/*! Unknown */
	Ref<NiInterpolator > interpolator6;
	/*! Unknown */
	Ref<NiInterpolator > interpolator7;
	/*! Unknown */
	Ref<NiInterpolator > interpolator8;
	/*! References interpolator for Amplitutde control. 0=straight, 50=wide */
	Ref<NiInterpolator > interpolator9_ArcOffset;
	/*! Unknown */
	unsigned short unknownShort1;
	/*! Unknown */
	unsigned short unknownShort2;
	/*! Unknown */
	unsigned short unknownShort3;
	/*! How far lightning will stretch to. */
	float distanceWeight;
	/*! Unknown */
	float float2;
	/*! How wide the bolt will be */
	float stripWidth;
	/*! Influences forking behavior */
	float fork;
	/*! Unknown */
	float float5;
	/*! Unknown */
	byte byte1;
	/*! Unknown */
	byte byte2;
	/*! Unknown */
	byte byte3;
	/*! Unknown, unsure if this is actually another interpolator link. */
	Ref<NiObject > interpolator10_;
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