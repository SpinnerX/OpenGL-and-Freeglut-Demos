#include "euler.h"


///////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv)
{
    initSharedMem();

    // init GLUT and GL
    initGLUT(argc, argv);
    initGL();

    // the last GLUT call (LOOP)
    // window will be shown and display callback is triggered by events
    // NOTE: this call never return main().
    glutMainLoop(); /* Start GLUT event-processing loop */

    return 0;
}



