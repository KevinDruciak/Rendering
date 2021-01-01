#include <cmath>
#include <Util/exceptions.h>
#include "scene.h"
#include "cylinder.h"

using namespace Ray;
using namespace Util;

//////////////
// Cylinder //
//////////////

void Cylinder::init( const LocalSceneData &data )
{
	// Set the material pointer
	if( _materialIndex<0 ) THROW( "negative material index: %d" , _materialIndex );
	else if( _materialIndex>=data.materials.size() ) THROW( "material index out of bounds: %d <= %d" , _materialIndex , (int)data.materials.size() );
	else _material = &data.materials[ _materialIndex ];

	//////////////////////////////////
	// Do any necessary set-up here //
	//////////////////////////////////
	WARN_ONCE( "method undefined" );
}

void Cylinder::updateBoundingBox( void )
{
	///////////////////////////////
	// Set the _bBox object here //
	///////////////////////////////
	Point3D p(radius, height / 2, radius);
	_bBox = BoundingBox3D(center - p, center + p);
}

void Cylinder::initOpenGL( void )
{
	/////////////////////////////////////////
	// Do any necessary OpenGL set-up here //
	/////////////////////////////////////////
	WARN_ONCE( "method undefined" );

	// Sanity check to make sure that OpenGL state is good
	ASSERT_OPEN_GL_STATE();
}

double Cylinder::intersect( Ray3D ray , RayShapeIntersectionInfo& iInfo , BoundingBox1D range , std::function< bool (double) > validityLambda ) const
{
	RayTracingStats::IncrementRayPrimitiveIntersectionNum();

	/////////////////////////////////////////////////////////////
	// Compute the intersection of the shape with the ray here //
	/////////////////////////////////////////////////////////////
	return INFINITY;
}

bool Cylinder::isInside( Point3D p ) const
{
	////////////////////////////////////////////////////////
	// Determine if the point is inside the cylinder here //
	////////////////////////////////////////////////////////
	THROW( "method undefined" );
	return false;
}

void Cylinder::drawOpenGL(GLSLProgram *glslProgram) const
{
	//////////////////////////////
	// Do OpenGL rendering here //
	//////////////////////////////
	glDisable(GL_CULL_FACE);
	this->_material->drawOpenGL(glslProgram);

	const double hSlices = height / OpenGLTessellationComplexity;
	const double vSlices = 2.0 * Pi / OpenGLTessellationComplexity;
	for (int i = 0; i < OpenGLTessellationComplexity; i++) {
		const double hSlice1 = 0.5 * height - static_cast<double>(i) * hSlices;
		const double hSlice2 = hSlice1 - hSlices;
		glBegin(GL_TRIANGLE_STRIP);
		for (int j = 0; j < OpenGLTessellationComplexity + 2; j++) {
			const double rot = static_cast<double>(j) * vSlices;
			const double x = radius * cos(rot);
			const double y = radius * sin(rot);
			glNormal3f(x / radius, y / radius, 0);
			glVertex3f(x, y, hSlice1);
			glNormal3f(x / radius, y / radius, 0);
			glVertex3f(x, y, hSlice2);
		}
		glEnd();
	}

	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(0, 0, 1);
	glVertex3f(center[0], center[1], height / 2);
	for (int i = 0; i <= OpenGLTessellationComplexity; i++) {
		glVertex3f(center[0] + (radius * cos(i *  (2 * Pi) / OpenGLTessellationComplexity)), center[1] + (radius * sin(i * (2 * Pi) / OpenGLTessellationComplexity)), height / 2);
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(0, 0, -1);
	glVertex3f(center[0], center[1], -height / 2);
	for (int i = 0; i <= OpenGLTessellationComplexity; i++) {
		glVertex3f(center[0] + (radius * cos(i *  (2 * Pi) / OpenGLTessellationComplexity)), center[1] + (radius * sin(i * (2 * Pi) / OpenGLTessellationComplexity)), -height / 2);
	}
	glEnd();

}