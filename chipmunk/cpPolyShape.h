/* Copyright (c) 2007 Scott Lembcke
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

// Axis structure used by cpPolyShape.
typedef struct cpPolyShapeAxis{
	// normal
	cpVect n;
	// distance from origin
	cpFloat d;
} cpPolyShapeAxis;

// Convex polygon shape structure.
typedef struct cpPolyShape{
	cpShape shape;
	
	// Vertex and axis lists.
	int numVerts;
	cpVect *verts;
	cpPolyShapeAxis *axes;

	// Transformed vertex and axis lists.
	cpVect *tVerts;
	cpPolyShapeAxis *tAxes;
} cpPolyShape;

// Basic allocation functions.
extern cpPolyShape *cpPolyShapeAlloc(void);
extern cpPolyShape *cpPolyShapeInit(cpPolyShape *poly, cpBody *body, int numVerts, cpVect *verts, cpVect offset);
extern cpShape *cpPolyShapeNew(cpBody *body, int numVerts, cpVect *verts, cpVect offset);

// Returns the minimum distance of the polygon to the axis.
static inline cpFloat
cpPolyShapeValueOnAxis(const cpPolyShape *poly, const cpVect n, const cpFloat d)
{
	int i;
	cpVect *verts = poly->tVerts;
	cpFloat min = cpvdot(n, verts[0]);
	
	for(i=1; i<poly->numVerts; i++)
		min = cpfmin(min, cpvdot(n, verts[i]));
	
	return min - d;
}

// Returns true if the polygon contains the vertex.
static inline int
cpPolyShapeContainsVert(cpPolyShape *poly, cpVect v)
{
	int i;
	cpPolyShapeAxis *axes = poly->tAxes;
	
	for(i=0; i<poly->numVerts; i++){
		cpFloat dist = cpvdot(axes[i].n, v) - axes[i].d;
		if(dist > 0.0) return 0;
	}
	
	return 1;
}
