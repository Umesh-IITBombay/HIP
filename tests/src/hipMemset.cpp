/*
Copyright (c) 2015-2016 Advanced Micro Devices, Inc. All rights reserved.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
// Simple test for memset.
// Also serves as a template for other tests.

#include "hip_runtime.h"
#include "test_common.h"


int main(int argc, char *argv[])
{

    HipTest::parseStandardArguments(argc, argv, true);

    size_t Nbytes = N*sizeof(char);

    printf ("N=%zu  memsetval=%2x\n", N, memsetval);

    char *A_d;
    char *A_h;

    HIPCHECK ( hipMalloc(&A_d, Nbytes) );
    A_h = (char*)malloc(Nbytes);

    HIPCHECK ( hipMemset(A_d, memsetval, Nbytes) ); 

    HIPCHECK ( hipMemcpy(A_h, A_d, Nbytes, hipMemcpyDeviceToHost));

    for (int i=0; i<N; i++) {
        if (A_h[i] != memsetval) {
            failed("mismatch at index:%d computed:%02x, memsetval:%02x\n", i, (int)A_h[i], (int)memsetval);

        }
    }

    passed();

}
