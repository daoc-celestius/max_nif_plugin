/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _NISCREENELEMENTSDATA_H_
#define _NISCREENELEMENTSDATA_H_

//--BEGIN FILE HEAD CUSTOM CODE--//

//--END CUSTOM CODE--//

#include "NiTriShapeData.h"

// Include structures
#include "../gen/Polygon.h"
namespace Niflib {

class NiScreenElementsData;
typedef Ref<NiScreenElementsData> NiScreenElementsDataRef;

/*! Two dimensional screen elements. */
class NiScreenElementsData : public NiTriShapeData {
public:
	/*! Constructor */
	NIFLIB_API NiScreenElementsData();

	/*! Destructor */
	NIFLIB_API virtual ~NiScreenElementsData();

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

	// Polygons
	// \return The current value.
	vector<Polygon > GetPolygons() const;

	// Polygons
	// \param[in] value The new value.
	void SetPolygons( const vector<Polygon >& value );

	// Polygon Indices
	// \return The current value.
	vector<unsigned short > GetPolygonIndices() const;

	// Polygon Indices
	// \param[in] value The new value.
	void SetPolygonIndices( const vector<unsigned short >& value );

	// Number of Polygons actually in use
	// \return The current value.
	unsigned short GetNumPolygons() const;

	// Number of Polygons actually in use
	// \param[in] value The new value.
	void SetNumPolygons( unsigned short value );

	// Number of in-use vertices
	// \return The current value.
	unsigned short GetUsedVertices() const;

	// Number of in-use vertices
	// \param[in] value The new value.
	void SetUsedVertices( unsigned short value );

	// Number of in-use triangles
	// \return The current value.
	unsigned short GetUsedTrianglePoints() const;

	// Number of in-use triangles
	// \param[in] value The new value.
	void SetUsedTrianglePoints( unsigned short value );

	****End Example Naive Implementation***/

	//--BEGIN MISC CUSTOM CODE--//

	//--END CUSTOM CODE--//
protected:
	/*! Maximum number of polygons? */
	mutable unsigned short maxPolygons;
	/*! Polygons */
	vector<Polygon > polygons;
	/*! Polygon Indices */
	vector<unsigned short > polygonIndices;
	/*! Unknown */
	unsigned short unknownUshort1;
	/*! Number of Polygons actually in use */
	unsigned short numPolygons;
	/*! Number of in-use vertices */
	unsigned short usedVertices;
	/*! Unknown */
	unsigned short unknownUshort2;
	/*! Number of in-use triangles */
	unsigned short usedTrianglePoints;
	/*! Maximum number of faces */
	unsigned short unknownUshort3;
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