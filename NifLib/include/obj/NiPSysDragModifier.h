/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _NIPSYSDRAGMODIFIER_H_
#define _NIPSYSDRAGMODIFIER_H_

//--BEGIN FILE HEAD CUSTOM CODE--//
//--END CUSTOM CODE--//

#include "NiPSysModifier.h"
namespace Niflib {

// Forward define of referenced NIF objects
class NiObject;
class NiPSysDragModifier;
typedef Ref<NiPSysDragModifier> NiPSysDragModifierRef;

/*! Unknown. */
class NiPSysDragModifier : public NiPSysModifier {
public:
	/*! Constructor */
	NIFLIB_API NiPSysDragModifier();

	/*! Destructor */
	NIFLIB_API virtual ~NiPSysDragModifier();

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

	// Parent reference.
	// \return The current value.
	NiObject * GetParent() const;

	// Parent reference.
	// \param[in] value The new value.
	void SetParent( NiObject * value );

	// The drag axis.
	// \return The current value.
	Vector3 GetDragAxis() const;

	// The drag axis.
	// \param[in] value The new value.
	void SetDragAxis( const Vector3 & value );

	// Drag percentage.
	// \return The current value.
	float GetPercentage() const;

	// Drag percentage.
	// \param[in] value The new value.
	void SetPercentage( float value );

	// The range.
	// \return The current value.
	float GetRange() const;

	// The range.
	// \param[in] value The new value.
	void SetRange( float value );

	// The range falloff.
	// \return The current value.
	float GetRangeFalloff() const;

	// The range falloff.
	// \param[in] value The new value.
	void SetRangeFalloff( float value );

	****End Example Naive Implementation***/

	//--BEGIN MISC CUSTOM CODE--//
	//--END CUSTOM CODE--//
protected:
	/*! Parent reference. */
	NiObject * parent;
	/*! The drag axis. */
	Vector3 dragAxis;
	/*! Drag percentage. */
	float percentage;
	/*! The range. */
	float range;
	/*! The range falloff. */
	float rangeFalloff;
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