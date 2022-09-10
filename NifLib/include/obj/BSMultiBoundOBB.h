/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _BSMULTIBOUNDOBB_H_
#define _BSMULTIBOUNDOBB_H_

//--BEGIN FILE HEAD CUSTOM CODE--//

//--END CUSTOM CODE--//

#include "BSMultiBoundData.h"
namespace Niflib {

class BSMultiBoundOBB;
typedef Ref<BSMultiBoundOBB> BSMultiBoundOBBRef;

/*! Oriented bounding box. */
class BSMultiBoundOBB : public BSMultiBoundData {
public:
	/*! Constructor */
	NIFLIB_API BSMultiBoundOBB();

	/*! Destructor */
	NIFLIB_API virtual ~BSMultiBoundOBB();

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

	// Center of the box.
	// \return The current value.
	Vector3 GetCenter() const;

	// Center of the box.
	// \param[in] value The new value.
	void SetCenter( const Vector3 & value );

	// Size of the box along each axis.
	// \return The current value.
	Vector3 GetSize() const;

	// Size of the box along each axis.
	// \param[in] value The new value.
	void SetSize( const Vector3 & value );

	// Rotation of the bounding box.
	// \return The current value.
	Matrix33 GetRotation() const;

	// Rotation of the bounding box.
	// \param[in] value The new value.
	void SetRotation( const Matrix33 & value );

	****End Example Naive Implementation***/

	//--BEGIN MISC CUSTOM CODE--//

	//--END CUSTOM CODE--//
protected:
	/*! Center of the box. */
	Vector3 center;
	/*! Size of the box along each axis. */
	Vector3 size;
	/*! Rotation of the bounding box. */
	Matrix33 rotation;
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