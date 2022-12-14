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
 
// NOTE: cpArray is rarely used and will probably go away.

typedef struct cpArray{
	int num, max;
	void **arr;
} cpArray;

typedef void (*cpArrayIter)(void *ptr, void *data);

extern cpArray *cpArrayAlloc(void);
extern cpArray *cpArrayInit(cpArray *arr, int size);
extern cpArray *cpArrayNew(int size);

extern void cpArrayDestroy(cpArray *arr);
extern void cpArrayFree(cpArray *arr);

extern void cpArrayClear(cpArray *arr);

extern void cpArrayPush(cpArray *arr, void *object);
extern void cpArrayDeleteIndex(cpArray *arr, int index);
extern void cpArrayDeleteObj(cpArray *arr, void *obj);

extern void cpArrayEach(cpArray *arr, cpArrayIter iterFunc, void *data);
extern int cpArrayContains(cpArray *arr, void *ptr);
