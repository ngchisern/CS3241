//============================================================
// STUDENT NAME: Ng Chi Sern
// NUS User ID.: e0550524
// COMMENTS TO GRADER: <TODO COMMENTS TO GRADER>
//
//============================================================

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

/////////////////////////////////////////////////////////////////////////////
// CONSTANTS
/////////////////////////////////////////////////////////////////////////////

#define PI                  3.1415926535897932384626433832795

#define MAX_NUM_OF_DISCS    200     // Limit the number of discs.
#define MIN_RADIUS          10.0    // Minimum radius of disc.
#define MAX_RADIUS          50.0    // Maximum radius of disc.
#define NUM_OF_SIDES        18      // Number of polygon sides to approximate a disc.

#define MIN_X_SPEED         1.0     // Minimum speed of disc in X direction.
#define MAX_X_SPEED         20.0    // Maximum speed of disc in X direction.
#define MIN_Y_SPEED         1.0     // Minimum speed of disc in Y direction.
#define MAX_Y_SPEED         20.0    // Maximum speed of disc in Y direction.

#define DESIRED_FPS         30      // Desired number of frames per second.


/////////////////////////////////////////////////////////////////////////////
// GLOBAL VARIABLES
/////////////////////////////////////////////////////////////////////////////

typedef struct discType
{
    double pos[2];          // The X and Y coordinates of the center of the disc.
    double speed[2];        // The velocity of the disc in X and Y directions. Can be negative.
    double radius;          // Radius of the disc.
    unsigned char color[3]; // RGB color of the disc. Each value is 0 to 255.
} discType;

/*
The 2D space in which the discs are located spans from the coordinates [0, 0],
which corresponds to the bottom-leftmost corner of the display window, to the
coordinates [winWidth, winHeight], which corresponds to the top-rightmost
corner of the display window.

The speed is measured as the distance moved in the above 2D space per
render frame time.
*/

int numDiscs = 0;                   // Number of discs that have been added.

discType disc[ MAX_NUM_OF_DISCS ];  // Array for storing discs.

bool drawWireframe = false;         // Draw polygons in wireframe if true,
// otherwise polygons are filled.

int winWidth = 800;                 // Window width in pixels.
int winHeight = 600;                // Window height in pixels.


/////////////////////////////////////////////////////////////////////////////
// Draw the disc in its color using GL_TRIANGLE_FAN.
/////////////////////////////////////////////////////////////////////////////

void DrawDisc( const discType *d )
{
    static bool firstTime = true;
    static double unitDiscVertex[ NUM_OF_SIDES + 1 ][2];

    if ( firstTime )
    {
        firstTime = false;

        // Pre-compute and store the vertices' positions of a unit-radius disc.

        //****************************
        //*** WRITE YOUR CODE HERE ***
        //****************************
        for (int i = 0; i < NUM_OF_SIDES + 1; i++) {
            double fraction = (double) i / NUM_OF_SIDES;
            unitDiscVertex[i][0] = cos(fraction * 2 * PI); // x-axis
            unitDiscVertex[i][1] = sin(fraction * 2 * PI); // y-axis
        }
    }

    // Draw the disc in its color as a GL_TRAINGLE_FAN.

    //****************************
    //*** WRITE YOUR CODE HERE ***
    //****************************
    glColor3b((GLbyte) d->color[0], (GLbyte)d->color[1], (GLbyte)d->color[2]);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f((GLfloat ) d->pos[0], (GLfloat) d->pos[1]);
    for (int i = 0; i < NUM_OF_SIDES + 1; i++) {
        glVertex2f(d->pos[0] + d->radius * unitDiscVertex[i][0],
                   d->pos[1] + d->radius * unitDiscVertex[i][1]);
    }
    glEnd();
}



/////////////////////////////////////////////////////////////////////////////
// The display callback function.
/////////////////////////////////////////////////////////////////////////////

void MyDisplay( void )
{
    glClear(GL_COLOR_BUFFER_BIT);

    if ( drawWireframe )
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    else
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

    for ( int i = 0; i < numDiscs; i++ ) DrawDisc( &disc[i] );

    glutSwapBuffers();
}



/////////////////////////////////////////////////////////////////////////////
// The mouse callback function.
// If mouse left button is pressed, a new disc is created with its center
// at the mouse cursor position. The new disc is assigned the followings:
// (1) a random radius between MIN_RADIUS and MAX_RADIUS,
// (2) a random speed in X direction in the range
//     from -MAX_X_SPEED to -MIN_X_SPEED, and from MIN_X_SPEED to MAX_X_SPEED.
// (3) a random speed in Y direction in the range
//     from -MAX_Y_SPEED to -MIN_Y_SPEED, and from MIN_Y_SPEED to MAX_Y_SPEED.
// (4) R, G, B color, each ranges from 0 to 255.
/////////////////////////////////////////////////////////////////////////////

void MyMouse( int btn, int state, int x, int y )
{
    if ( btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN )
    {
        if ( numDiscs >= MAX_NUM_OF_DISCS )
            printf( "Already reached maximum number of discs.\n" );
        else
        {
            disc[ numDiscs ].pos[0] = x;
            disc[ numDiscs ].pos[1] = winHeight - 1 - y;

            disc[ numDiscs ].color[0] = random() % 256;
            disc[ numDiscs ].color[1] = random() % 256;
            disc[ numDiscs ].color[2] = random() % 256;

            //****************************
            //*** WRITE YOUR CODE HERE ***
            //****************************
            disc[ numDiscs ].radius = (double) random() / RAND_MAX * (MAX_RADIUS - MIN_RADIUS) + MIN_RADIUS;

            disc [ numDiscs ].speed[0] = (double) random() / RAND_MAX * (MAX_X_SPEED - MIN_X_SPEED) + MIN_X_SPEED;
            if (random() % 2 == 1) {
                disc [ numDiscs ].speed[0] *= -1;
            }
            disc [ numDiscs ].speed[1] = (double) random() / RAND_MAX * (MAX_Y_SPEED - MIN_Y_SPEED) + MIN_Y_SPEED;
            disc [ numDiscs ].speed[1] = (double) random() / RAND_MAX * (MAX_Y_SPEED - MIN_Y_SPEED) + MIN_Y_SPEED;
            if (random() % 2 == 1) {
                disc [ numDiscs ].speed[1] *= -1;
            }

            numDiscs++;
            glutPostRedisplay();
        }
    }
}



/////////////////////////////////////////////////////////////////////////////
// The reshape callback function.
// It also sets up the viewing.
/////////////////////////////////////////////////////////////////////////////

void MyReshape( int w, int h )
{
    winWidth = w;
    winHeight = h;

    glViewport( 0, 0, w, h );

    glMatrixMode( GL_PROJECTION );

    //****************************
    //*** WRITE YOUR CODE HERE ***
    //****************************
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
}



/////////////////////////////////////////////////////////////////////////////
// The keyboard callback function.
/////////////////////////////////////////////////////////////////////////////

void MyKeyboard( unsigned char key, int x, int y )
{
    switch ( key )
    {
        // Quit program.
        case 'q':
        case 'Q': exit(0);
            break;

            // Toggle wireframe or filled polygons.
        case 'w':
        case 'W': drawWireframe = !drawWireframe;
            glutPostRedisplay();
            break;

            // Reset and erase all discs.
        case 'r':
        case 'R': numDiscs = 0;
            glutPostRedisplay();
            break;
    }
}



/////////////////////////////////////////////////////////////////////////////
// Updates the positions of all the discs.
//
// Increments the position of each disc by its speed in each of the
// X and Y directions. Note that the speeds can be negative.
// At its new position, if the disc is entirely or partially outside the
// left window boundary, then shift it right so that it is inside the
// window and just touches the left window boundary. Its speed in the X
// direction must now be reversed (negated). Similar approach is
// applied for the cases of the right, top, and bottom window boundaries.
/////////////////////////////////////////////////////////////////////////////

void UpdateAllDiscPos( void )
{
    for ( int i = 0; i < numDiscs; i++ )
    {
        //****************************
        //*** WRITE YOUR CODE HERE ***
        //****************************
        disc[i].pos[0] += disc[i].speed[0];
        disc[i].pos[1] += disc[i].speed[1];

        if (disc[i].pos[0] - disc[i].radius <= 0 || disc[i].pos[0] + disc[i].radius >= winWidth - 1) {
            disc[i].speed[0] *= -1;
            if (disc[i].pos[0] - disc[i].radius <= 0) {
                disc[i].pos[0] = disc[i].radius;
            } else {
                disc[i].pos[0] = winWidth - disc[i].radius - 1;
            }
        }

        if (disc[i].pos[1] - disc[i].radius <= 0 || disc[i].pos[1] + disc[i].radius >= winHeight - 1) {
            disc[i].speed[1] *= -1;
            if (disc[i].pos[1] - disc[i].radius <= 0) {
                disc[i].pos[1] = disc[i].radius;
            } else {
                disc[i].pos[1] = winHeight - disc[i].radius - 1;
            }
        }
    }
    glutPostRedisplay();
}



/////////////////////////////////////////////////////////////////////////////
// The timer callback function.
/////////////////////////////////////////////////////////////////////////////

void MyTimer( int v )
{
    //****************************
    //*** WRITE YOUR CODE HERE ***
    //****************************
    glutTimerFunc(1 * 1000 / DESIRED_FPS, MyTimer, v);
    UpdateAllDiscPos();
}



/////////////////////////////////////////////////////////////////////////////
// The init function. It initializes some OpenGL states.
/////////////////////////////////////////////////////////////////////////////

void MyInit( void )
{
    glClearColor( 0.0, 0.0, 0.0, 1.0 ); // Black background color.
    glShadeModel( GL_FLAT );
}



static void WaitForEnterKeyBeforeExit(void)
{
    printf("Press Enter to exit.\n");
    fflush(stdin);
    getchar();
}



/////////////////////////////////////////////////////////////////////////////
// The main function.
/////////////////////////////////////////////////////////////////////////////

int main( int argc, char** argv )
{
    atexit(WaitForEnterKeyBeforeExit); // atexit() is declared in stdlib.h

    glutInit( &argc, argv );

    glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE );  //*** MODIFY THIS ***

    glutInitWindowSize( winWidth, winHeight );
    glutCreateWindow( "main" );

    MyInit();

    // Register the callback functions.
    glutDisplayFunc( MyDisplay );
    glutReshapeFunc( MyReshape );
    glutMouseFunc( MyMouse );
    glutKeyboardFunc( MyKeyboard );

    // glutIdleFunc( UpdateAllDiscPos );  //*** MODIFY THIS ***
    MyTimer(0);

    // Display user instructions in console window.
    printf( "Click LEFT MOUSE BUTTON in window to add new disc.\n" );
    printf( "Press 'w' to toggle wireframe.\n" );
    printf( "Press 'r' to erase all discs.\n" );
    printf( "Press 'q' to quit.\n\n" );

    // Enter GLUT event loop.
    glutMainLoop();
    return 0;
}
