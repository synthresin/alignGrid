#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"
#include "cinder/Perlin.h"

#define GRID_NUM 40
using namespace ci;
using namespace ci::app;
using namespace std;



class alignGridApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
    void redraw();
    
    float mGridSizeX;
    float mGridSizeY;
    Rand mRand;
    Perlin mPerlin;
};

void alignGridApp::setup()
{
    setWindowSize(600, 600);
    gl::enableAlphaBlending();
    mGridSizeX = (float)getWindowWidth()/ GRID_NUM;
    mGridSizeY = (float)getWindowHeight()/ GRID_NUM;
    printf("xsize : %f, ysize : %f" , mGridSizeX, mGridSizeY);
    //gl::clear(ColorA(0.85,0.92,0.88));
    gl::clear(ColorA(1,1,1));
}

void alignGridApp::mouseDown( MouseEvent event )
{
    redraw();
}

void alignGridApp::update()
{
}

void alignGridApp::draw()
{
	// clear out the window with black
	
}

void alignGridApp::redraw()
{
    //gl::clear(ColorA(0.85,0.92,0.88));
    gl::clear(ColorA(1,1,1));
    float multiplier = 100.8746f;
    for(int yGrid = 0; yGrid < GRID_NUM; yGrid++) {
        for (int xGrid = 0; xGrid < GRID_NUM; xGrid++) {
            
            int gridMode;
            //int gridMode = mRand.nextInt(0,3);
            float noise =( mPerlin.fBm( Vec2f(xGrid * multiplier, yGrid * multiplier)) + 1.0f )  /2;
            if(noise >= 0 && noise < 0.43f) {
                gridMode = 0;
            } else if(noise >= 0.43f && noise < 0.48f) {
                gridMode = 1;
            } else gridMode = 2;
            float opacity = mRand.nextFloat();
            
            float xInit = mGridSizeX * xGrid;
            float yInit = mGridSizeY * yGrid;
            
            switch (gridMode) {
                case 0:
                    glLineWidth(7.0f);
                    gl::color(0.86f,0.38f,0.47f, opacity);
                    gl::drawSolidCircle(Vec2f(xInit, yInit), 3.5f);
                    gl::drawLine(Vec2f(xInit, yInit), Vec2f(xInit + mGridSizeX, yInit + mGridSizeY) );
                    gl::drawSolidCircle(Vec2f(xInit + mGridSizeX, yInit + mGridSizeY),3.5f);
                    break;
                    
                case 1:
                    glLineWidth(3.0f);
                    gl::color(ColorA(0.46f, 0.76f, 0.83f, opacity));
                    gl::drawLine(Vec2f(xInit+mGridSizeX, yInit), Vec2f(xInit, yInit + mGridSizeY) );
                    break;
                    
                default:
                    break;
            }
            
            
        }
    }
}


CINDER_APP_BASIC( alignGridApp, RendererGl )
