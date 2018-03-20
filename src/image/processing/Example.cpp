#include <wx/wx.h>
#include "window.h"
#include <wx/image.h>
#include <wx/dcmemory.h>
#include <wx/dcclient.h>
#include <wx/dc.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include <math.h>
using namespace std;

static const wxChar *FILETYPES = _T("All files (*.*)|*.*");

IMPLEMENT_APP(BasicApplication)

bool BasicApplication::OnInit()
{
  wxInitAllImageHandlers();
  MyFrame *frame = new MyFrame(_("Basic Frame"), 50, 50, 700, 400);
  frame->Show(TRUE);
  SetTopWindow(frame);
  return TRUE;
}

MyFrame::MyFrame(const wxString title, int xpos, int ypos, int width, int height): wxFrame((wxFrame *) NULL, -1, title, wxPoint(xpos, ypos), wxSize(width, height)){

  fileMenu = new wxMenu;
  fileMenu->Append(LOAD_FILE_ID, _T("&Open file\tCTRL-O"));
  fileMenu->Append(RAWLOAD_FILE_ID, _T("&Open RAW file"));
  fileMenu->AppendSeparator();
//###########################################################//
//----------------------START MY MENU -----------------------//
//###########################################################//

  fileMenu->Append(INVERT_IMAGE_ID, _T("&Invert image"));
  fileMenu->Append(SCALE_IMAGE_ID, _T("&Scale image"));
  fileMenu->Append(UNDO_IMAGE_ID, _T("&Undo and reset picture\tCTRL-Z"));
  fileMenu->Append(ROI_IMAGE_ID, _T("Set Region of interest")); //--->Works?
  fileMenu->Append(RESCALE_IMAGE_ID, _T("&Rescale image"));//--->To be modified!

//###########################################################//
//----------------------END MY MENU -------------------------//
//###########################################################//

  fileMenu->AppendSeparator();
  fileMenu->Append(SAVE_IMAGE_ID, _T("&Save image"));
  fileMenu->Append(EXIT_ID, _T("E&xit\tCTRL-W"));

  menuBar = new wxMenuBar;
  menuBar->Append(fileMenu, _T("&File"));

  SetMenuBar(menuBar);
  CreateStatusBar(3);
  oldWidth = 0;
  oldHeight = 0;
  loadedImage = 0;///////////////////////////////////////////////////


//////////////////////////////////////////////////////////////NextFileMenu

fileMenuw = new wxMenu;
  fileMenuw->Append(LOAD_FILE_ID, _T("&Open file"));
  fileMenuw->AppendSeparator();
//###########################################################//
//----------------------START MY MENU -----------------------//
//###########################################################//

 fileMenuw->Append(SHIFTING_IMAGE_ID, _T("&Shifting"));
 fileMenuw->Append(AVERAGING_IMAGE_ID, _T("&Averaging"));
 fileMenuw->Append(WEIGHTED_IMAGE_ID, _T("&Weighted Averaging"));
 fileMenuw->Append(FLAPLACIAN_IMAGE_ID, _T("&4 Neighbour Laplacian"));
 fileMenuw->Append(ELAPLACIAN_IMAGE_ID, _T("&8 Neighbour Laplacian"));
 fileMenuw->Append(FLAPLACIANE_IMAGE_ID, _T("&4 Neighbour Laplacian Enhancement"));
 fileMenuw->Append(ELAPLACIANE_IMAGE_ID, _T("&8 Neighbour Laplacian Enhancement"));
 fileMenuw->Append(ROBERTS_IMAGE_ID, _T("&Roberts Filtering"));
 fileMenuw->Append(SOBELX_IMAGE_ID, _T("&Sobel X"));
 fileMenuw->Append(SOBELY_IMAGE_ID, _T("&Sobel Y"));

//###########################################################//
//----------------------END MY MENU -------------------------//
//###########################################################//

  fileMenuw->AppendSeparator();
  fileMenuw->Append(SAVE_IMAGE_ID, _T("&Save image"));
  fileMenuw->Append(EXIT_ID, _T("E&xit"));


  menuBar->Append(fileMenuw, _T("&Lab5"));

  SetMenuBar(menuBar);
  CreateStatusBar(3);
  oldWidth = 0;
  oldHeight = 0;
  loadedImage = 0;

////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////NextFileMenu

fileMenuq = new wxMenu;
  fileMenuq->Append(LOAD_FILE_ID, _T("&Open file"));
  fileMenuq->AppendSeparator();
//###########################################################//
//----------------------START MY MENU -----------------------//
//###########################################################//
 fileMenuq->Append(SALTANDPEPPER_IMAGE_ID, _T("&Salt and Pepper Filtering"));
 fileMenuq->Append(MINFILTERING_IMAGE_ID, _T("&MinFiltering"));
 fileMenuq->Append(MAXFILTERING_IMAGE_ID, _T("&MaxFiltering"));
 fileMenuq->Append(MIDPOINTFILTERING_IMAGE_ID, _T("&MidpointFiltering"));
 fileMenuq->Append(MEDIANFILTERING_IMAGE_ID, _T("&MedianFiltering"));

//###########################################################//
//----------------------END MY MENU -------------------------//
//###########################################################//

  fileMenuq->AppendSeparator();
  fileMenuq->Append(SAVE_IMAGE_ID, _T("&Save image"));
  fileMenuq->Append(EXIT_ID, _T("E&xit"));


  menuBar->Append(fileMenuq, _T("&Lab6"));

  SetMenuBar(menuBar);
  CreateStatusBar(3);
  oldWidth = 0;
  oldHeight = 0;
  loadedImage = 0;

////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////NextFileMenu

fileMenue = new wxMenu;
  fileMenue->Append(LOAD_FILE_ID, _T("&Open file"));
  fileMenue->AppendSeparator();
//###########################################################//
//----------------------START MY MENU -----------------------//
//###########################################################//

 fileMenue->Append(NEGATIVE_IMAGE_ID, _T("&Negative"));
 fileMenue->Append(LOGARITHMIC_IMAGE_ID, _T("&Logarithm"));
 fileMenue->Append(POWERLAW_IMAGE_ID, _T("&Powerlaw"));
 fileMenue->Append(RANDOMLOOKUP_IMAGE_ID, _T("&Random Look Up"));

//###########################################################//
//----------------------END MY MENU -------------------------//
//###########################################################//

  fileMenue->AppendSeparator();
  fileMenue->Append(SAVE_IMAGE_ID, _T("&Save image"));
  fileMenue->Append(EXIT_ID, _T("&Exit"));


  menuBar->Append(fileMenue, _T("&Lab7"));

  SetMenuBar(menuBar);
  CreateStatusBar(3);
  oldWidth = 0;
  oldHeight = 0;
  loadedImage = 0;

////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////NextFileMenu

fileMenuq = new wxMenu;
  fileMenuq->Append(LOAD_FILE_ID, _T("&Open file"));
  fileMenuq->AppendSeparator();

//###########################################################//
//----------------------START MY MENU -----------------------//
//###########################################################//
 fileMenuq->Append(HISTOGRAM_IMAGE_ID, _T("&Equalise Histogram"));

//###########################################################//
//----------------------END MY MENU -------------------------//
//###########################################################//

  fileMenuq->AppendSeparator();
  fileMenuq->Append(SAVE_IMAGE_ID, _T("&Save image"));
  fileMenuq->Append(EXIT_ID, _T("E&xit"));


  menuBar->Append(fileMenuq, _T("&Lab8"));

  SetMenuBar(menuBar);
  CreateStatusBar(3);
  oldWidth = 0;
  oldHeight = 0;
  loadedImage = 0;

////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////NextFileMenu

fileMenuq = new wxMenu;
  fileMenuq->Append(LOAD_FILE_ID, _T("&Open file"));
  fileMenuq->AppendSeparator();

//###########################################################//
//----------------------START MY MENU -----------------------//
//###########################################################//
 fileMenuq->Append(MEAN_IMAGE_ID, _T("&Mean Histogram"));
 fileMenuq->Append(STANDARDDEVIATION_IMAGE_ID, _T("&Standard Deviation Histogram"));
 fileMenuq->Append(STHRESHOLDING_IMAGE_ID, _T("&Simple Thresholding"));
 fileMenuq->Append(ATHRESHOLDING_IMAGE_ID, _T("&Automated Thresholding"));

//###########################################################//
//----------------------END MY MENU -------------------------//
//###########################################################//

  fileMenuq->AppendSeparator();
  fileMenuq->Append(SAVE_IMAGE_ID, _T("&Save image"));
  fileMenuq->Append(EXIT_ID, _T("E&xit"));


  menuBar->Append(fileMenuq, _T("&Lab9"));

  SetMenuBar(menuBar);
  CreateStatusBar(3);
  oldWidth = 0;
  oldHeight = 0;
  loadedImage = 0;

////////////////////////////////////////////////////////////////////


/* initialise the variables that we added */
  imgWidth = imgHeight = 0;
  stuffToDraw = 0;

}

MyFrame::~MyFrame(){
/* release resources */
  if(loadedImage){
    loadedImage->Destroy();
    loadedImage = 0;
  }

}

/*
 */

void MyFrame::OnOpenFile(wxCommandEvent & event){
    wxFileDialog *openFileDialog = new wxFileDialog ( this, _T("Open file"),
                                                      _T(""""), _T(""""), FILETYPES, wxOPEN, wxDefaultPosition);
    if(openFileDialog->ShowModal() == wxID_OK){
        wxString filename = openFileDialog->GetFilename();
        wxString path = openFileDialog->GetPath();
        printf("Loading image form file...");
        loadedImage = new wxImage(path); //Image Loaded form file
        loadedImage2 = new wxImage(path);
        if(loadedImage->Ok()){
            stuffToDraw = ORIGINAL_IMG;    // set the display flag
            printf("Done! \n");
        }
        else {
            printf("error:...");
            loadedImage->Destroy();
            loadedImage = 0;
        }
        Refresh();
    }
}


//###########################################################//
//-----------------------------------------------------------//
//---------- DO NOT MODIFY THE CODE ABOVE--------------------//
//-----------------------------------------------------------//
//###########################################################//


//INVERT IMAGE
void MyFrame::OnInvertImage(wxCommandEvent & event){

    printf("Inverting...");
    free(loadedImage);
    loadedImage = new wxImage(bitmap.ConvertToImage());

    for( int i=0;i<imgWidth;i++)
        for(int j=0;j<imgHeight;j++){
            loadedImage->SetRGB(i,j,255-loadedImage->GetRed(i,j),
                                255-loadedImage->GetGreen(i,j),
                                255-loadedImage->GetBlue(i,j));
        }

    printf(" Finished inverting.\n");
    Refresh();
}



//IMAGE SCALEING
void MyFrame::OnScaleImage(wxCommandEvent & event){

    printf("Scaling...");
    free(loadedImage);
    loadedImage = new wxImage(bitmap.ConvertToImage());

    for( int i=0;i<imgWidth;i++)
        for(int j=0;j<imgHeight;j++){
            loadedImage->SetRGB(i,j,2.5* loadedImage->GetRed(i,j),
                                2.5* loadedImage->GetGreen(i,j),
                                2.5* loadedImage->GetBlue(i,j));
        }

    printf(" Finished scaling.\n");
    Refresh();
}
//Undo Image
void MyFrame::UndoImage(wxCommandEvent & event){

    printf("RESET!");
	wxImage *undo = new wxImage (imgWidth,imgHeight, true);

    free(loadedImage);

    undo = loadedImage2;
    loadedImage = new wxImage(undo -> Copy());




    Refresh();
}
//////////////////////////////////////////////
//////////////////////////////////////////////
/////////////////////////////////////////////
//Scaling

void MyFrame::Rescale(wxCommandEvent & event){

    float random_number = (rand () % 21);
    printf("Scale function..");
    free(loadedImage);
    loadedImage = new wxImage(bitmap.ConvertToImage());

    float r,g,b;
    int newr,newg,newb;

    for( int i=0;i<imgWidth;i++)
        for(int j=0;j<imgHeight;j++){
            r = loadedImage->GetRed(i,j);
            g = loadedImage->GetGreen(i,j);
            b = loadedImage->GetBlue(i,j);

            r *= random_number/10;
            g *= random_number/10;
            b *= random_number/10;


            if(r > 255)
            {
                r = 255;
            }
            else if (r < 0)
            {
                r = 0;
            }

            if(g > 255)
            {
                g = 255;
            }
            else if (g < 0)
            {
                g = 0;
            }


            if(b > 255)
            {
                b = 255;
            }
            else if (b < 0)
            {
                b = 0;
            }

            newr = int(r);
            newg = int(g);
            newb = int(b);

            loadedImage->SetRGB(i,j,newr,newg,newb);
            cout<<newr<< "  ";
        }

    printf ("Random number= %g", random_number);
    printf(" Finished rescale.\n");

    Refresh();


}





//###########################################################//
//-----------------------------------------------------------//
//---------- LAB5 -------------------
//-----------------------------------------------------------//
//###########################################################//
//lab5 exercise 1 shifting
void MyFrame::Shifting(wxCommandEvent & event){

    float random_number = (rand () % 511)-255;
    printf("Shift function..");
    free(loadedImage);
    loadedImage = new wxImage(bitmap.ConvertToImage());
    int r,g,b;

    for( int i=0;i<imgWidth;i++)
        for(int j=0;j<imgHeight;j++){
            r = loadedImage->GetRed(i,j);   // red pixel value
            g = loadedImage->GetGreen(i,j); // green pixel value
            b = loadedImage->GetBlue(i,j); // blue pixel value

            r=r + random_number;
            g=g + random_number;
            b=b + random_number;

            if(r > 255)
            {
                r = 255;
            }
            else if (r < 0)
            {
                r = 0;
            }

            if(g > 255)
            {
                g = 255;
            }
            else if (g < 0)
            {
                g = 0;
            }


            if(b > 255)
            {
                b = 255;
            }
            else if (b < 0)
            {
                b = 0;
            }
            loadedImage->SetRGB(i,j,r,g,b);
        }

    printf ("Random number= %g", random_number);
    printf(" Finished shifting.\n");

    Refresh();


}


//lab5 exercise 2 averaging
void MyFrame::Averaging(wxCommandEvent & event){

    printf("Averaging");
    free(loadedImage);
    loadedImage = new wxImage(bitmap.ConvertToImage());
	int r,g,b;
	int m1,n1,v1;
	int m2,n2,v2;
	int m3,n3,v3;
	int m4,n4,v4;
	int m5,n5,v5;
	int m6,n6,v6;
	int m7,n7,v7;
	int m8,n8,v8;
	int m9,n9,v9;
	int counter = 0;
	int* averagesumred = new int[3000000];
	int* averagesumgreen = new int[3000000];
	int* averagesumblue = new int[3000000];

	for(int i=1; i<imgWidth-1; i++)
        for(int j=1; j<imgHeight-1; j++)
        {
            m1 = loadedImage->GetRed(i-1,j-1) ;
            m2 = loadedImage->GetRed(i,j-1) ;
            m3 = loadedImage->GetRed(i+1,j-1) ;
            m4 = loadedImage->GetRed(i-1, j) ;
            m5 = loadedImage->GetRed(i, j) ;
            m6 = loadedImage->GetRed(i+1, j);
            m7 = loadedImage->GetRed(i-1, j+1) ;
            m8 = loadedImage->GetRed(i, j+1) ;
            m9 = loadedImage->GetRed(i+1, j+1) ;
            counter = m1 + m2 + m3 + m4 + m5 + m6 + m7 + m8 + m9;
            averagesumred[i] = counter/9;
            n1 = loadedImage->GetGreen(i-1,j-1) ;
            n2 = loadedImage->GetGreen(i,j-1) ;
            n3 = loadedImage->GetGreen(i+1,j-1) ;
            n4 = loadedImage->GetGreen(i-1, j) ;
            n5 = loadedImage->GetGreen(i, j) ;
            n6 = loadedImage->GetGreen(i+1, j);
            n7 = loadedImage->GetGreen(i-1, j+1) ;
            n8 = loadedImage->GetGreen(i, j+1) ;
            n9 = loadedImage->GetGreen(i+1, j+1) ;
            counter = n1 + n2 + n3 + n4 + n5 + n6 + n7 + n8 + n9;

            averagesumgreen[i] = counter/9;
            v1 = loadedImage->GetBlue(i-1,j-1) ;
            v2 = loadedImage->GetBlue(i,j-1) ;
            v3 = loadedImage->GetBlue(i+1,j-1) ;
            v4 = loadedImage->GetBlue(i-1, j) ;
            v5 = loadedImage->GetBlue(i, j) ;
            v6 = loadedImage->GetBlue(i+1, j);
            v7 = loadedImage->GetBlue(i-1, j+1) ;
            v8 = loadedImage->GetBlue(i, j+1) ;
            v9 = loadedImage->GetBlue(i+1, j+1) ;
            counter = v1 + v2 + v3 + v4 + v5 + v6 + v7 + v8 + v9;


            averagesumblue[i] = counter/9;
            loadedImage->SetRGB(i,j,averagesumred[i],averagesumgreen[i],averagesumblue[i]);
        }

    printf(" Finished average mask.\n");

    Refresh();


}

//lab5 exercise 2 weighted averaging
void MyFrame::Weighted(wxCommandEvent & event){

    printf("My function...");
    free(loadedImage);
    loadedImage = new wxImage(bitmap.ConvertToImage());
	int r,g,b;
	int m1,n1,v1;
	int m2,n2,v2;
	int m3,n3,v3;
	int m4,n4,v4;
	int m5,n5,v5;
	int m6,n6,v6;
	int m7,n7,v7;
	int m8,n8,v8;
	int m9,n9,v9;
	int counterr = 0;
	int counterb = 0;
	int counterg = 0;
    int averagesumred [imgWidth][imgHeight];
    int averagesumgreen [imgWidth][imgHeight];
    int averagesumblue [imgWidth][imgHeight];
    int mask [3][3];

	int arraycount= 0;
	for(int i=0; i<imgWidth-1; i++)
        for(int j=0; j<imgHeight-1; j++)
        {
            mask[0][0] = 1;
            mask[1][0] = 2;
            mask[2][0] = 1;
            mask[0][1] = 2;
            mask[1][1] = 4;
            mask[2][1] = 2;
            mask[0][2] = 1;
            mask[1][2] = 2;
            mask[2][2] = 1;


            m1 = loadedImage->GetRed(0+i,0+j) ;
            m2 = loadedImage->GetRed(1+i,j) ;
            m3 = loadedImage->GetRed(2+i,j) ;
            m4 = loadedImage->GetRed(0+i, 1+j) ;
            m5 = loadedImage->GetRed(1+i, 1+j) ;
            m6 = loadedImage->GetRed(i+2, 1+j);
            m7 = loadedImage->GetRed(i+0, j+2) ;
            m8 = loadedImage->GetRed(i+1, j+2) ;
            m9 = loadedImage->GetRed(i+2, j+2) ;
            counterr = m1*mask[0][0] + m2*mask[1][0] + m3*mask[2][0] + m4*mask[0][1] + m5*mask[1][1] + m6*mask[2][1] + m7*mask[0][2] + m8*mask[1][2] + m9*mask[2][2];
            averagesumred[i][j] = counterr/16;
//green
            n1 = loadedImage->GetGreen(i,j) ;
            n2 = loadedImage->GetGreen(i+1,j) ;
            n3 = loadedImage->GetGreen(i+2,j) ;
            n4 = loadedImage->GetGreen(i, j+1) ;
            n5 = loadedImage->GetGreen(i+1, j+1) ;
            n6 = loadedImage->GetGreen(i+2, j+1);
            n7 = loadedImage->GetGreen(i, j+2) ;
            n8 = loadedImage->GetGreen(i+1, j+2) ;
            n9 = loadedImage->GetGreen(i+2, j+2) ;
            counterg = n1*mask[0][0] + n2*mask[1][0] + n3*mask[2][0] + n4*mask[0][1] + n5*mask[1][1] + n6*mask[2][1] + n7*mask[0][2] + n8*mask[1][2] + n9*mask[2][2];

            averagesumgreen[i][j] = counterg/16;

            v1 = loadedImage->GetBlue(i,j) ;
            v2 = loadedImage->GetBlue(i+1,j) ;
            v3 = loadedImage->GetBlue(i+2,j) ;
            v4 = loadedImage->GetBlue(i, j+1) ;
            v5 = loadedImage->GetBlue(i+1, j+1) ;
            v6 = loadedImage->GetBlue(i+2, j+1);
            v7 = loadedImage->GetBlue(i, j+2) ;
            v8 = loadedImage->GetBlue(i+1, j+2) ;
            v9 = loadedImage->GetBlue(i+2, j+2) ;
            counterb = v1*mask[0][0] + v2*mask[1][0] + v3*mask[2][0] + v4*mask[0][1] + v5*mask[1][1] + v6*mask[2][1] + v7*mask[0][2] + v8*mask[1][2] + v9*mask[2][2];

            averagesumblue[i][j] = counterb/16;

        }


	for(int i=0; i<imgWidth; i++)
	{

        for(int j=0; j<imgHeight; j++)
        {
            if(averagesumred[i][j]<0)
            {
                averagesumred[i][j] = 0;
            }
            if(averagesumred[i][j]>255)
            {
                averagesumred[i][j] = 255;
            }
            if(averagesumgreen[i][j]<0)
            {
                averagesumgreen[i][j] = 0;
            }
            if(averagesumgreen[i][j]>255)
            {
                averagesumgreen[i][j] = 255;
            }
            if(averagesumblue[i][j]<0)
            {
                averagesumblue[i][j] = 0;
            }
            if(averagesumblue[i][j]>255)
            {
                averagesumblue[i][j] = 255;
            }

            loadedImage->SetRGB(i,j,averagesumred[i][j],averagesumgreen[i][j],averagesumblue[i][j]);
        }
	}


    printf(" Finished weighted averaging.\n");

    Refresh();

}

//lab5 exercise 2 4 laplacian
void MyFrame::FLaplacian(wxCommandEvent & event){

    printf("Laplacian");

    free(loadedImage);
    loadedImage = new wxImage(bitmap.ConvertToImage());
	int r,g,b;
	int m1,n1,v1;
	int m2,n2,v2;
	int m3,n3,v3;
	int m4,n4,v4;
	int m5,n5,v5;
	int m6,n6,v6;
	int m7,n7,v7;
	int m8,n8,v8;
	int m9,n9,v9;
	int counterr = 0;
	int counterb = 0;
	int counterg = 0;
    int averagesumred [imgWidth][imgHeight];
    int averagesumgreen [imgWidth][imgHeight];
    int averagesumblue [imgWidth][imgHeight];
    int mask [3][3];

	int arraycount= 0;

	for(int i=0; i<imgWidth-1; i++)
        for(int j=0; j<imgHeight-1; j++)
        {
            mask[0][0] = 0;
            mask[1][0] = -1;
            mask[2][0] = 0;
            mask[0][1] = -1;
            mask[1][1] = 4;
            mask[2][1] = -1;
            mask[0][2] = 0;
            mask[1][2] = -1;
            mask[2][2] = 0;


            m1 = loadedImage->GetRed(0+i,0+j) ;
            m2 = loadedImage->GetRed(1+i,j) ;
            m3 = loadedImage->GetRed(2+i,j) ;
            m4 = loadedImage->GetRed(0+i, 1+j) ;
            m5 = loadedImage->GetRed(1+i, 1+j) ;
            m6 = loadedImage->GetRed(i+2, 1+j);
            m7 = loadedImage->GetRed(i+0, j+2) ;
            m8 = loadedImage->GetRed(i+1, j+2) ;
            m9 = loadedImage->GetRed(i+2, j+2) ;
            counterr = m1*mask[0][0] + m2*mask[1][0] + m3*mask[2][0] + m4*mask[0][1] + m5*mask[1][1] + m6*mask[2][1] + m7*mask[0][2] + m8*mask[1][2] + m9*mask[2][2];
            averagesumred[i][j] = counterr;
//green


            n1 = loadedImage->GetGreen(i,j) ;
            n2 = loadedImage->GetGreen(i+1,j) ;
            n3 = loadedImage->GetGreen(i+2,j) ;
            n4 = loadedImage->GetGreen(i, j+1) ;
            n5 = loadedImage->GetGreen(i+1, j+1) ;
            n6 = loadedImage->GetGreen(i+2, j+1);
            n7 = loadedImage->GetGreen(i, j+2) ;
            n8 = loadedImage->GetGreen(i+1, j+2) ;
            n9 = loadedImage->GetGreen(i+2, j+2) ;
            counterg = n1*mask[0][0] + n2*mask[1][0] + n3*mask[2][0] + n4*mask[0][1] + n5*mask[1][1] + n6*mask[2][1] + n7*mask[0][2] + n8*mask[1][2] + n9*mask[2][2];

            averagesumgreen[i][j] = counterg;
//blue

            v1 = loadedImage->GetBlue(i,j) ;
            v2 = loadedImage->GetBlue(i+1,j) ;
            v3 = loadedImage->GetBlue(i+2,j) ;
            v4 = loadedImage->GetBlue(i, j+1) ;
            v5 = loadedImage->GetBlue(i+1, j+1) ;
            v6 = loadedImage->GetBlue(i+2, j+1);
            v7 = loadedImage->GetBlue(i, j+2) ;
            v8 = loadedImage->GetBlue(i+1, j+2) ;
            v9 = loadedImage->GetBlue(i+2, j+2) ;
            counterb = v1*mask[0][0] + v2*mask[1][0] + v3*mask[2][0] + v4*mask[0][1] + v5*mask[1][1] + v6*mask[2][1] + v7*mask[0][2] + v8*mask[1][2] + v9*mask[2][2];

            averagesumblue[i][j] = counterb;

        }


	for(int i=0; i<imgWidth; i++)
	{

        for(int j=0; j<imgHeight; j++)
        {
            if(averagesumred[i][j]<0)
            {
                averagesumred[i][j] = 0;
            }
            if(averagesumred[i][j]>255)
            {
                averagesumred[i][j] = 255;
            }
            if(averagesumgreen[i][j]<0)
            {
                averagesumgreen[i][j] = 0;
            }
            if(averagesumgreen[i][j]>255)
            {
                averagesumgreen[i][j] = 255;
            }
            if(averagesumblue[i][j]<0)
            {
                averagesumblue[i][j] = 0;
            }
            if(averagesumblue[i][j]>255)
            {
                averagesumblue[i][j] = 255;
            }



            loadedImage->SetRGB(i,j,averagesumred[i][j],averagesumgreen[i][j],averagesumblue[i][j]);
        }
	}

    printf(" Finished 4 neighbour laplacian.\n");

    Refresh();


}

//lab5 exercise 2 8 laplacian
void MyFrame::ELaplacian(wxCommandEvent & event){



    free(loadedImage);
    loadedImage = new wxImage(bitmap.ConvertToImage());
	int r,g,b;
	int m1,n1,v1;
	int m2,n2,v2;
	int m3,n3,v3;
	int m4,n4,v4;
	int m5,n5,v5;
	int m6,n6,v6;
	int m7,n7,v7;
	int m8,n8,v8;
	int m9,n9,v9;
	int counterr = 0;
	int counterb = 0;
	int counterg = 0;
    int averagesumred [imgWidth][imgHeight];
    int averagesumgreen [imgWidth][imgHeight];
    int averagesumblue [imgWidth][imgHeight];
    int mask [3][3];

	int arraycount= 0;

	for(int i=0; i<imgWidth-1; i++)
        for(int j=0; j<imgHeight-1; j++)
        {
            mask[0][0] = -1;
            mask[1][0] = -1;
            mask[2][0] = -1;
            mask[0][1] = -1;
            mask[1][1] = 8;
            mask[2][1] = -1;
            mask[0][2] = -1;
            mask[1][2] = -1;
            mask[2][2] = -1;


            m1 = loadedImage->GetRed(0+i,0+j) ;
            m2 = loadedImage->GetRed(1+i,j) ;
            m3 = loadedImage->GetRed(2+i,j) ;
            m4 = loadedImage->GetRed(0+i, 1+j) ;
            m5 = loadedImage->GetRed(1+i, 1+j) ;
            m6 = loadedImage->GetRed(i+2, 1+j);
            m7 = loadedImage->GetRed(i+0, j+2) ;
            m8 = loadedImage->GetRed(i+1, j+2) ;
            m9 = loadedImage->GetRed(i+2, j+2) ;
            counterr = m1*mask[0][0] + m2*mask[1][0] + m3*mask[2][0] + m4*mask[0][1] + m5*mask[1][1] + m6*mask[2][1] + m7*mask[0][2] + m8*mask[1][2] + m9*mask[2][2];
            averagesumred[i][j] = counterr;
//green


            n1 = loadedImage->GetGreen(i,j) ;
            n2 = loadedImage->GetGreen(i+1,j) ;
            n3 = loadedImage->GetGreen(i+2,j) ;
            n4 = loadedImage->GetGreen(i, j+1) ;
            n5 = loadedImage->GetGreen(i+1, j+1) ;
            n6 = loadedImage->GetGreen(i+2, j+1);
            n7 = loadedImage->GetGreen(i, j+2) ;
            n8 = loadedImage->GetGreen(i+1, j+2) ;
            n9 = loadedImage->GetGreen(i+2, j+2) ;
            counterg = n1*mask[0][0] + n2*mask[1][0] + n3*mask[2][0] + n4*mask[0][1] + n5*mask[1][1] + n6*mask[2][1] + n7*mask[0][2] + n8*mask[1][2] + n9*mask[2][2];

            averagesumgreen[i][j] = counterg;
//blue

            v1 = loadedImage->GetBlue(i,j) ;
            v2 = loadedImage->GetBlue(i+1,j) ;
            v3 = loadedImage->GetBlue(i+2,j) ;
            v4 = loadedImage->GetBlue(i, j+1) ;
            v5 = loadedImage->GetBlue(i+1, j+1) ;
            v6 = loadedImage->GetBlue(i+2, j+1);
            v7 = loadedImage->GetBlue(i, j+2) ;
            v8 = loadedImage->GetBlue(i+1, j+2) ;
            v9 = loadedImage->GetBlue(i+2, j+2) ;
            counterb = v1*mask[0][0] + v2*mask[1][0] + v3*mask[2][0] + v4*mask[0][1] + v5*mask[1][1] + v6*mask[2][1] + v7*mask[0][2] + v8*mask[1][2] + v9*mask[2][2];

            averagesumblue[i][j] = counterb;

        }


	for(int i=0; i<imgWidth; i++)
	{

        for(int j=0; j<imgHeight; j++)
        {
            if(averagesumred[i][j]<0)
            {
                averagesumred[i][j] = 0;
            }
            if(averagesumred[i][j]>255)
            {
                averagesumred[i][j] = 255;
            }
            if(averagesumgreen[i][j]<0)
            {
                averagesumgreen[i][j] = 0;
            }
            if(averagesumgreen[i][j]>255)
            {
                averagesumgreen[i][j] = 255;
            }
            if(averagesumblue[i][j]<0)
            {
                averagesumblue[i][j] = 0;
            }
            if(averagesumblue[i][j]>255)
            {
                averagesumblue[i][j] = 255;
            }



            loadedImage->SetRGB(i,j,averagesumred[i][j],averagesumgreen[i][j],averagesumblue[i][j]);
        }
	}


    printf(" Finished 8 neighbour laplacian.\n");

    Refresh();



}

//lab5 exercise 2 enhanced 4 lapalacian
void MyFrame::FLaplacianE(wxCommandEvent & event){



    free(loadedImage);
    loadedImage = new wxImage(bitmap.ConvertToImage());
	int r,g,b;
	int m1,n1,v1;
	int m2,n2,v2;
	int m3,n3,v3;
	int m4,n4,v4;
	int m5,n5,v5;
	int m6,n6,v6;
	int m7,n7,v7;
	int m8,n8,v8;
	int m9,n9,v9;
	int counterr = 0;
	int counterb = 0;
	int counterg = 0;
    int averagesumred [imgWidth][imgHeight];
    int averagesumgreen [imgWidth][imgHeight];
    int averagesumblue [imgWidth][imgHeight];
    int mask [3][3];

	int arraycount= 0;

	for(int i=0; i<imgWidth-1; i++)
        for(int j=0; j<imgHeight-1; j++)
        {
            mask[0][0] = 0;
            mask[1][0] = -1;
            mask[2][0] = 0;
            mask[0][1] = -1;
            mask[1][1] = 5;
            mask[2][1] = -1;
            mask[0][2] = 0;
            mask[1][2] = -1;
            mask[2][2] = 0;


            m1 = loadedImage->GetRed(0+i,0+j) ;
            m2 = loadedImage->GetRed(1+i,j) ;
            m3 = loadedImage->GetRed(2+i,j) ;
            m4 = loadedImage->GetRed(0+i, 1+j) ;
            m5 = loadedImage->GetRed(1+i, 1+j) ;
            m6 = loadedImage->GetRed(i+2, 1+j);
            m7 = loadedImage->GetRed(i+0, j+2) ;
            m8 = loadedImage->GetRed(i+1, j+2) ;
            m9 = loadedImage->GetRed(i+2, j+2) ;
            counterr = m1*mask[0][0] + m2*mask[1][0] + m3*mask[2][0] + m4*mask[0][1] + m5*mask[1][1] + m6*mask[2][1] + m7*mask[0][2] + m8*mask[1][2] + m9*mask[2][2];
            averagesumred[i][j] = counterr;
//green


            n1 = loadedImage->GetGreen(i,j) ;
            n2 = loadedImage->GetGreen(i+1,j) ;
            n3 = loadedImage->GetGreen(i+2,j) ;
            n4 = loadedImage->GetGreen(i, j+1) ;
            n5 = loadedImage->GetGreen(i+1, j+1) ;
            n6 = loadedImage->GetGreen(i+2, j+1);
            n7 = loadedImage->GetGreen(i, j+2) ;
            n8 = loadedImage->GetGreen(i+1, j+2) ;
            n9 = loadedImage->GetGreen(i+2, j+2) ;
            counterg = n1*mask[0][0] + n2*mask[1][0] + n3*mask[2][0] + n4*mask[0][1] + n5*mask[1][1] + n6*mask[2][1] + n7*mask[0][2] + n8*mask[1][2] + n9*mask[2][2];

            averagesumgreen[i][j] = counterg;
//blue

            v1 = loadedImage->GetBlue(i,j) ;
            v2 = loadedImage->GetBlue(i+1,j) ;
            v3 = loadedImage->GetBlue(i+2,j) ;
            v4 = loadedImage->GetBlue(i, j+1) ;
            v5 = loadedImage->GetBlue(i+1, j+1) ;
            v6 = loadedImage->GetBlue(i+2, j+1);
            v7 = loadedImage->GetBlue(i, j+2) ;
            v8 = loadedImage->GetBlue(i+1, j+2) ;
            v9 = loadedImage->GetBlue(i+2, j+2) ;
//add m1 to m9, then divide by 9. that'll be average
            counterb = v1*mask[0][0] + v2*mask[1][0] + v3*mask[2][0] + v4*mask[0][1] + v5*mask[1][1] + v6*mask[2][1] + v7*mask[0][2] + v8*mask[1][2] + v9*mask[2][2];

//	arraycount+=1;
            averagesumblue[i][j] = counterb;

        }


	for(int i=0; i<imgWidth; i++)
	{

        for(int j=0; j<imgHeight; j++)
        {
            if(averagesumred[i][j]<0)
            {
                averagesumred[i][j] = 0;
            }
            if(averagesumred[i][j]>255)
            {
                averagesumred[i][j] = 255;
            }
            if(averagesumgreen[i][j]<0)
            {
                averagesumgreen[i][j] = 0;
            }
            if(averagesumgreen[i][j]>255)
            {
                averagesumgreen[i][j] = 255;
            }
            if(averagesumblue[i][j]<0)
            {
                averagesumblue[i][j] = 0;
            }
            if(averagesumblue[i][j]>255)
            {
                averagesumblue[i][j] = 255;
            }



            loadedImage->SetRGB(i,j,averagesumred[i][j],averagesumgreen[i][j],averagesumblue[i][j]);
        }
	}


    printf(" Finished 4 neighbour enhanced laplacian.\n");

    Refresh();



}

//lab5 exercise 2 enhanced 8 laplacian
void MyFrame::ELaplacianE(wxCommandEvent & event){



    free(loadedImage);
    loadedImage = new wxImage(bitmap.ConvertToImage());
	int r,g,b;
	int m1,n1,v1;
	int m2,n2,v2;
	int m3,n3,v3;
	int m4,n4,v4;
	int m5,n5,v5;
	int m6,n6,v6;
	int m7,n7,v7;
	int m8,n8,v8;
	int m9,n9,v9;
	int counterr = 0;
	int counterb = 0;
	int counterg = 0;
    int averagesumred [imgWidth][imgHeight];
    int averagesumgreen [imgWidth][imgHeight];
    int averagesumblue [imgWidth][imgHeight];
    int mask [3][3];

	int arraycount= 0;

    //mask multiplying by values on the image
	for(int i=0; i<imgWidth-1; i++)
        for(int j=0; j<imgHeight-1; j++)
        {
            mask[0][0] = -1;
            mask[1][0] = -1;
            mask[2][0] = -1;
            mask[0][1] = -1;
            mask[1][1] = 9;
            mask[2][1] = -1;
            mask[0][2] = -1;
            mask[1][2] = -1;
            mask[2][2] = -1;


            m1 = loadedImage->GetRed(0+i,0+j) ;
            m2 = loadedImage->GetRed(1+i,j) ;
            m3 = loadedImage->GetRed(2+i,j) ;
            m4 = loadedImage->GetRed(0+i, 1+j) ;
            m5 = loadedImage->GetRed(1+i, 1+j) ;
            m6 = loadedImage->GetRed(i+2, 1+j);
            m7 = loadedImage->GetRed(i+0, j+2) ;
            m8 = loadedImage->GetRed(i+1, j+2) ;
            m9 = loadedImage->GetRed(i+2, j+2) ;
//add m1 to m9, then divide by 16 multiply all by weighted average. that'll be average
            counterr = m1*mask[0][0] + m2*mask[1][0] + m3*mask[2][0] + m4*mask[0][1] + m5*mask[1][1] + m6*mask[2][1] + m7*mask[0][2] + m8*mask[1][2] + m9*mask[2][2];
            averagesumred[i][j] = counterr;
//green


            n1 = loadedImage->GetGreen(i,j) ;
            n2 = loadedImage->GetGreen(i+1,j) ;
            n3 = loadedImage->GetGreen(i+2,j) ;
            n4 = loadedImage->GetGreen(i, j+1) ;
            n5 = loadedImage->GetGreen(i+1, j+1) ;
            n6 = loadedImage->GetGreen(i+2, j+1);
            n7 = loadedImage->GetGreen(i, j+2) ;
            n8 = loadedImage->GetGreen(i+1, j+2) ;
            n9 = loadedImage->GetGreen(i+2, j+2) ;
//add m1 to m9, then divide by 9. that'll be average
            counterg = n1*mask[0][0] + n2*mask[1][0] + n3*mask[2][0] + n4*mask[0][1] + n5*mask[1][1] + n6*mask[2][1] + n7*mask[0][2] + n8*mask[1][2] + n9*mask[2][2];

            averagesumgreen[i][j] = counterg;
//blue

            v1 = loadedImage->GetBlue(i,j) ;
            v2 = loadedImage->GetBlue(i+1,j) ;
            v3 = loadedImage->GetBlue(i+2,j) ;
            v4 = loadedImage->GetBlue(i, j+1) ;
            v5 = loadedImage->GetBlue(i+1, j+1) ;
            v6 = loadedImage->GetBlue(i+2, j+1);
            v7 = loadedImage->GetBlue(i, j+2) ;
            v8 = loadedImage->GetBlue(i+1, j+2) ;
            v9 = loadedImage->GetBlue(i+2, j+2) ;
//add m1 to m9, then divide by 9. that'll be average
            counterb = v1*mask[0][0] + v2*mask[1][0] + v3*mask[2][0] + v4*mask[0][1] + v5*mask[1][1] + v6*mask[2][1] + v7*mask[0][2] + v8*mask[1][2] + v9*mask[2][2];

            averagesumblue[i][j] = counterb;

        }


	for(int i=0; i<imgWidth; i++)
	{

        for(int j=0; j<imgHeight; j++)
        {
            if(averagesumred[i][j]<0)
            {
                averagesumred[i][j] = 0;
            }
            if(averagesumred[i][j]>255)
            {
                averagesumred[i][j] = 255;
            }
            if(averagesumgreen[i][j]<0)
            {
                averagesumgreen[i][j] = 0;
            }
            if(averagesumgreen[i][j]>255)
            {
                averagesumgreen[i][j] = 255;
            }
            if(averagesumblue[i][j]<0)
            {
                averagesumblue[i][j] = 0;
            }
            if(averagesumblue[i][j]>255)
            {
                averagesumblue[i][j] = 255;
            }



            loadedImage->SetRGB(i,j,averagesumred[i][j],averagesumgreen[i][j],averagesumblue[i][j]);
        }
	}

    printf(" Finished 8 neighbour laplacian enhanced.\n");

    Refresh();




}

//lab5 exercise 2 roberts
void MyFrame::Roberts(wxCommandEvent & event){


    free(loadedImage);
    loadedImage = new wxImage(bitmap.ConvertToImage());
	int r,g,b;
	int m1,n1,v1;
	int m2,n2,v2;
	int m3,n3,v3;
	int m4,n4,v4;
	int m5,n5,v5;
	int m6,n6,v6;
	int m7,n7,v7;
	int m8,n8,v8;
	int m9,n9,v9;

	int counterr = 0;
	int counterb = 0;
	int counterg = 0;

    int averagesumred [imgWidth][imgHeight];
    int averagesumgreen [imgWidth][imgHeight];
    int averagesumblue [imgWidth][imgHeight];

    int mask [3][3];
    int mask2 [3][3];
    int mask3 [3][3];

	for(int i=0; i<imgWidth-1; i++)
        for(int j=0; j<imgHeight-1; j++)
        {
            mask[0][0] = 0;
            mask[1][0] = 0;
            mask[2][0] = 0;
            mask[0][1] = 0;
            mask[1][1] = 0;
            mask[2][1] = -1;
            mask[0][2] = 0;
            mask[1][2] = 1;
            mask[2][2] = 0;
            mask2[0][0] = 0;
            mask2[1][0] = 0;
            mask2[2][0] = 0;
            mask2[0][1] = 0;
            mask2[1][1] = -1;
            mask2[2][1] = 0;
            mask2[0][2] = 0;
            mask2[1][2] = 0;
            mask2[2][2] = 1;
//add masks together
            mask3[0][0] = mask[0][0]+mask2[0][0];
            mask3[1][0] = mask[1][0]+mask2[1][0];
            mask3[2][0] = mask[2][0]+mask2[2][0];
            mask3[0][1] = mask[0][1]+mask2[0][1];
            mask3[1][1] = mask[1][1]+mask2[1][1];
            mask3[2][1] = mask[2][1]+mask2[2][1];
            mask3[0][2] = mask[0][2]+mask2[0][2];
            mask3[1][2] = mask[1][2]+mask2[1][2];
            mask3[2][2] = mask[2][2]+mask2[2][2];
//red 1st roberts
            m1 = loadedImage->GetRed(0+i,0+j) ;
            m2 = loadedImage->GetRed(1+i,j) ;
            m3 = loadedImage->GetRed(2+i,j) ;
            m4 = loadedImage->GetRed(0+i, 1+j) ;
            m5 = loadedImage->GetRed(1+i, 1+j) ;
            m6 = loadedImage->GetRed(i+2, 1+j);
            m7 = loadedImage->GetRed(i+0, j+2) ;
            m8 = loadedImage->GetRed(i+1, j+2) ;
            m9 = loadedImage->GetRed(i+2, j+2) ;

            counterr = m1*mask3[0][0] + m2*mask3[1][0] + m3*mask3[2][0] + m4*mask3[0][1] + m5*mask3[1][1] + m6*mask3[2][1] + m7*mask3[0][2] + m8*mask3[1][2] + m9*mask3[2][2];

            averagesumred[i][j] = counterr;
//green
            n1 = loadedImage->GetGreen(i,j) ;
            n2 = loadedImage->GetGreen(i+1,j) ;
            n3 = loadedImage->GetGreen(i+2,j) ;
            n4 = loadedImage->GetGreen(i, j+1) ;
            n5 = loadedImage->GetGreen(i+1, j+1) ;
            n6 = loadedImage->GetGreen(i+2, j+1);
            n7 = loadedImage->GetGreen(i, j+2) ;
            n8 = loadedImage->GetGreen(i+1, j+2) ;
            n9 = loadedImage->GetGreen(i+2, j+2) ;

            counterg = n1*mask3[0][0] + n2*mask3[1][0] + n3*mask3[2][0] + n4*mask3[0][1] + n5*mask3[1][1] + n6*mask3[2][1] + n7*mask3[0][2] + n8*mask3[1][2] + n9*mask3[2][2];

            averagesumgreen[i][j] = counterg;


//blue

            v1 = loadedImage->GetBlue(i,j) ;
            v2 = loadedImage->GetBlue(i+1,j) ;
            v3 = loadedImage->GetBlue(i+2,j) ;
            v4 = loadedImage->GetBlue(i, j+1) ;
            v5 = loadedImage->GetBlue(i+1, j+1) ;
            v6 = loadedImage->GetBlue(i+2, j+1);
            v7 = loadedImage->GetBlue(i, j+2) ;
            v8 = loadedImage->GetBlue(i+1, j+2) ;
            v9 = loadedImage->GetBlue(i+2, j+2) ;

            counterb = v1*mask3[0][0] + v2*mask3[1][0] + v3*mask3[2][0] + v4*mask3[0][1] + v5*mask3[1][1] + v6*mask3[2][1] + v7*mask3[0][2] + v8*mask3[1][2] + v9*mask3[2][2];


            averagesumblue[i][j] = counterb;



        }


	for(int i=0; i<imgWidth; i++)
	{

        for(int j=0; j<imgHeight; j++)
        {

            if(averagesumred[i][j]<0)
            {
                averagesumred[i][j] = 0;
            }
            if(averagesumred[i][j]>255)
            {
                averagesumred[i][j] = 255;
            }
            if(averagesumgreen[i][j]<0)
            {
                averagesumgreen[i][j] = 0;
            }
            if(averagesumgreen[i][j]>255)
            {
                averagesumgreen[i][j] = 255;
            }
            if(averagesumblue[i][j]<0)
            {
                averagesumblue[i][j] = 0;
            }
            if(averagesumblue[i][j]>255)
            {
                averagesumblue[i][j] = 255;
            }



            loadedImage->SetRGB(i,j,averagesumred[i][j],averagesumgreen[i][j],averagesumblue[i][j]);
        }
	}


    printf(" Finished roberts mask.\n");

    Refresh();




}

//lab5 exercise 2 sobel x
void MyFrame::Sobelx(wxCommandEvent & event){


    printf("My function...");
    free(loadedImage);
    loadedImage = new wxImage(bitmap.ConvertToImage());
	int r,g,b;
	int m1,n1,v1;
	int m2,n2,v2;
	int m3,n3,v3;
	int m4,n4,v4;
	int m5,n5,v5;
	int m6,n6,v6;
	int m7,n7,v7;
	int m8,n8,v8;
	int m9,n9,v9;
	int counterr = 0;
	int counterb = 0;
	int counterg = 0;
    int averagesumred [imgWidth][imgHeight];
    int averagesumgreen [imgWidth][imgHeight];
    int averagesumblue [imgWidth][imgHeight];
    int mask [3][3];


    //mask multiplying by values on the image
	for(int i=0; i<imgWidth-1; i++)
        for(int j=0; j<imgHeight-1; j++)
        {
            mask[0][0] = -1;
            mask[1][0] = 0;
            mask[2][0] = 1;
            mask[0][1] = -2;
            mask[1][1] = 0;
            mask[2][1] = 2;
            mask[0][2] = -1;
            mask[1][2] = 0;
            mask[2][2] = 1;


            m1 = loadedImage->GetRed(0+i,0+j) ;
            m2 = loadedImage->GetRed(1+i,j) ;
            m3 = loadedImage->GetRed(2+i,j) ;
            m4 = loadedImage->GetRed(0+i, 1+j) ;
            m5 = loadedImage->GetRed(1+i, 1+j) ;
            m6 = loadedImage->GetRed(i+2, 1+j);
            m7 = loadedImage->GetRed(i+0, j+2) ;
            m8 = loadedImage->GetRed(i+1, j+2) ;
            m9 = loadedImage->GetRed(i+2, j+2) ;
//add m1 to m9, then divide by 16 multiply all by weighted average. that'll be average
            counterr = m1*mask[0][0] + m2*mask[1][0] + m3*mask[2][0] + m4*mask[0][1] + m5*mask[1][1] + m6*mask[2][1] + m7*mask[0][2] + m8*mask[1][2] + m9*mask[2][2];
            averagesumred[i][j] = abs(counterr);
            //cout<<averagesumred[i]<< "  ";
//green


            n1 = loadedImage->GetGreen(i,j) ;
            n2 = loadedImage->GetGreen(i+1,j) ;
            n3 = loadedImage->GetGreen(i+2,j) ;
            n4 = loadedImage->GetGreen(i, j+1) ;
            n5 = loadedImage->GetGreen(i+1, j+1) ;
            n6 = loadedImage->GetGreen(i+2, j+1);
            n7 = loadedImage->GetGreen(i, j+2) ;
            n8 = loadedImage->GetGreen(i+1, j+2) ;
            n9 = loadedImage->GetGreen(i+2, j+2) ;
//add m1 to m9, then divide by 9. that'll be average
            counterg = n1*mask[0][0] + n2*mask[1][0] + n3*mask[2][0] + n4*mask[0][1] + n5*mask[1][1] + n6*mask[2][1] + n7*mask[0][2] + n8*mask[1][2] + n9*mask[2][2];

            averagesumgreen[i][j] = abs(counterg);
//blue

            v1 = loadedImage->GetBlue(i,j) ;
            v2 = loadedImage->GetBlue(i+1,j) ;
            v3 = loadedImage->GetBlue(i+2,j) ;
            v4 = loadedImage->GetBlue(i, j+1) ;
            v5 = loadedImage->GetBlue(i+1, j+1) ;
            v6 = loadedImage->GetBlue(i+2, j+1);
            v7 = loadedImage->GetBlue(i, j+2) ;
            v8 = loadedImage->GetBlue(i+1, j+2) ;
            v9 = loadedImage->GetBlue(i+2, j+2) ;
//add m1 to m9, then divide by 9. that'll be average
            counterb = v1*mask[0][0] + v2*mask[1][0] + v3*mask[2][0] + v4*mask[0][1] + v5*mask[1][1] + v6*mask[2][1] + v7*mask[0][2] + v8*mask[1][2] + v9*mask[2][2];

            averagesumblue[i][j] = abs(counterb);

        }


	for(int i=0; i<imgWidth; i++)
	{

        for(int j=0; j<imgHeight; j++)
        {
            if(averagesumred[i][j]<0)
            {
                averagesumred[i][j] = 0;
            }
            if(averagesumred[i][j]>255)
            {
                averagesumred[i][j] = 255;
            }
            if(averagesumgreen[i][j]<0)
            {
                averagesumgreen[i][j] = 0;
            }
            if(averagesumgreen[i][j]>255)
            {
                averagesumgreen[i][j] = 255;
            }
            if(averagesumblue[i][j]<0)
            {
                averagesumblue[i][j] = 0;
            }
            if(averagesumblue[i][j]>255)
            {
                averagesumblue[i][j] = 255;
            }



            loadedImage->SetRGB(i,j,averagesumred[i][j],averagesumgreen[i][j],averagesumblue[i][j]);
        }
	}

    printf(" Finished sobel x.\n");

    Refresh();
}

//lab5 exercise 2 sobel y
void MyFrame::Sobely(wxCommandEvent & event){

    free(loadedImage);
    loadedImage = new wxImage(bitmap.ConvertToImage());
	int r,g,b;
	int m1,n1,v1;
	int m2,n2,v2;
	int m3,n3,v3;
	int m4,n4,v4;
	int m5,n5,v5;
	int m6,n6,v6;
	int m7,n7,v7;
	int m8,n8,v8;
	int m9,n9,v9;
	int counterr = 0;
	int counterb = 0;
	int counterg = 0;
    int averagesumred [imgWidth][imgHeight];
    int averagesumgreen [imgWidth][imgHeight];
    int averagesumblue [imgWidth][imgHeight];
    int mask [3][3];

	int arraycount= 0;
    //mask multiplying by values on the image
	for(int i=0; i<imgWidth-1; i++)
        for(int j=0; j<imgHeight-1; j++)
        {
            mask[0][0] = -1;
            mask[1][0] = -2;
            mask[2][0] = -1;
            mask[0][1] = 0;
            mask[1][1] = 0;
            mask[2][1] = 0;
            mask[0][2] = 1;
            mask[1][2] = 2;
            mask[2][2] = 1;


            m1 = loadedImage->GetRed(0+i,0+j) ;
            m2 = loadedImage->GetRed(1+i,j) ;
            m3 = loadedImage->GetRed(2+i,j) ;
            m4 = loadedImage->GetRed(0+i, 1+j) ;
            m5 = loadedImage->GetRed(1+i, 1+j) ;
            m6 = loadedImage->GetRed(i+2, 1+j);
            m7 = loadedImage->GetRed(i+0, j+2) ;
            m8 = loadedImage->GetRed(i+1, j+2) ;
            m9 = loadedImage->GetRed(i+2, j+2) ;
            counterr = m1*mask[0][0] + m2*mask[1][0] + m3*mask[2][0] + m4*mask[0][1] + m5*mask[1][1] + m6*mask[2][1] + m7*mask[0][2] + m8*mask[1][2] + m9*mask[2][2];
            averagesumred[i][j] = counterr;
//green


            n1 = loadedImage->GetGreen(i,j) ;
            n2 = loadedImage->GetGreen(i+1,j) ;
            n3 = loadedImage->GetGreen(i+2,j) ;
            n4 = loadedImage->GetGreen(i, j+1) ;
            n5 = loadedImage->GetGreen(i+1, j+1) ;
            n6 = loadedImage->GetGreen(i+2, j+1);
            n7 = loadedImage->GetGreen(i, j+2) ;
            n8 = loadedImage->GetGreen(i+1, j+2) ;
            n9 = loadedImage->GetGreen(i+2, j+2) ;
            counterg = n1*mask[0][0] + n2*mask[1][0] + n3*mask[2][0] + n4*mask[0][1] + n5*mask[1][1] + n6*mask[2][1] + n7*mask[0][2] + n8*mask[1][2] + n9*mask[2][2];

            averagesumgreen[i][j] = counterg;
//blue

            v1 = loadedImage->GetBlue(i,j) ;
            v2 = loadedImage->GetBlue(i+1,j) ;
            v3 = loadedImage->GetBlue(i+2,j) ;
            v4 = loadedImage->GetBlue(i, j+1) ;
            v5 = loadedImage->GetBlue(i+1, j+1) ;
            v6 = loadedImage->GetBlue(i+2, j+1);
            v7 = loadedImage->GetBlue(i, j+2) ;
            v8 = loadedImage->GetBlue(i+1, j+2) ;
            v9 = loadedImage->GetBlue(i+2, j+2) ;
//add m1 to m9, then divide by 9. that'll be average
            counterb = v1*mask[0][0] + v2*mask[1][0] + v3*mask[2][0] + v4*mask[0][1] + v5*mask[1][1] + v6*mask[2][1] + v7*mask[0][2] + v8*mask[1][2] + v9*mask[2][2];

            averagesumblue[i][j] = counterb;

        }


	for(int i=0; i<imgWidth; i++)
	{

        for(int j=0; j<imgHeight; j++)
        {
            if(averagesumred[i][j]<0)
            {
                averagesumred[i][j] = 0;
            }
            if(averagesumred[i][j]>255)
            {
                averagesumred[i][j] = 255;
            }
            if(averagesumgreen[i][j]<0)
            {
                averagesumgreen[i][j] = 0;
            }
            if(averagesumgreen[i][j]>255)
            {
                averagesumgreen[i][j] = 255;
            }
            if(averagesumblue[i][j]<0)
            {
                averagesumblue[i][j] = 0;
            }
            if(averagesumblue[i][j]>255)
            {
                averagesumblue[i][j] = 255;
            }



            loadedImage->SetRGB(i,j,averagesumred[i][j],averagesumgreen[i][j],averagesumblue[i][j]);
        }
	}


    printf(" Finished sobel y.\n");

    Refresh();
}





//###########################################################//
//-----------------------------------------------------------//
//---------- LAB6 -------------------
//-----------------------------------------------------------//
//###########################################################//

//lab6 exercise 1 saltandpepper
void MyFrame::SaltandPepperFiltering(wxCommandEvent & event){


    free(loadedImage);
    loadedImage = new wxImage(bitmap.ConvertToImage());


    unsigned char r,g,b;
	int saltandpepper = (imgHeight*imgWidth)/10;

	for (int i=0; i<saltandpepper;i++)
	{
        int x = (rand () % imgHeight);
        int y = (rand () % imgWidth);
        int z = (rand () % 5);

        r = loadedImage->GetRed(x,y);   // red pixel value
        g = loadedImage->GetGreen(x,y); // green pixel value
        b = loadedImage->GetBlue(x,y); // blue pixel value

        if(z == 1)
        {
            r = 255; g=255; b=255;
        }
        else if(z == 3)
        {
            r = 0; g = 0; b = 0;
        }

        loadedImage->SetRGB(x,y,r,g,b);
    }

    printf(" Finished salt and pepper.\n");

    Refresh();




}

//lab6 exercise2 maxfiltering
void MyFrame::MaxFiltering(wxCommandEvent & event){


    printf("Max Filtering...");
    free(loadedImage);
    loadedImage = new wxImage(bitmap.ConvertToImage());
	int r,g,b;
	int m1,n1,v1;
	int m2,n2,v2;
	int m3,n3,v3;
	int m4,n4,v4;
	int m5,n5,v5;
	int m6,n6,v6;
	int m7,n7,v7;
	int m8,n8,v8;
	int m9,n9,v9;
	int counterr = 0;
	int counterb = 0;
	int counterg = 0;
    int averagesumred [imgWidth][imgHeight];
    int averagesumgreen [imgWidth][imgHeight];
    int averagesumblue [imgWidth][imgHeight];
    int mask [3][3];


	for(int i=0; i<imgWidth-1; i++)
        for(int j=0; j<imgHeight-1; j++)
        {

            int tempred = 0;
            int tempgreen = 0;
            int tempblue = 0;

            m1 = loadedImage->GetRed(0+i,0+j) ;
            m2 = loadedImage->GetRed(1+i,j) ;
            m3 = loadedImage->GetRed(2+i,j) ;
            m4 = loadedImage->GetRed(0+i, 1+j) ;
            m5 = loadedImage->GetRed(1+i, 1+j) ;
            m6 = loadedImage->GetRed(i+2, 1+j);
            m7 = loadedImage->GetRed(i+0, j+2) ;
            m8 = loadedImage->GetRed(i+1, j+2) ;
            m9 = loadedImage->GetRed(i+2, j+2) ;

            int redarray[9] = {m1,m2,m3,m4,m5,m6,m7,m8,m9};

            for(int z = 0; z<9; z++)
            {
                if (redarray[z]>tempred)
                    tempred=redarray[z];
            }
//add m1 to m9, then divide by 16 multiply all by weighted average. that'll be average

            averagesumred[i][j] = tempred;


            n1 = loadedImage->GetGreen(i,j) ;
            n2 = loadedImage->GetGreen(i+1,j) ;
            n3 = loadedImage->GetGreen(i+2,j) ;
            n4 = loadedImage->GetGreen(i, j+1) ;
            n5 = loadedImage->GetGreen(i+1, j+1) ;
            n6 = loadedImage->GetGreen(i+2, j+1);
            n7 = loadedImage->GetGreen(i, j+2) ;
            n8 = loadedImage->GetGreen(i+1, j+2) ;
            n9 = loadedImage->GetGreen(i+2, j+2) ;
//add m1 to m9, then divide by 9. that'll be average

            int greenarray[9] = {m1,m2,m3,m4,m5,m6,m7,m8,m9};

            for(int z = 0; z<9; z++)
            {
                if (greenarray[z]>tempgreen)
                    tempgreen=greenarray[z];
            }



            averagesumgreen[i][j] = tempgreen;
//blue

            v1 = loadedImage->GetBlue(i,j) ;
            v2 = loadedImage->GetBlue(i+1,j) ;
            v3 = loadedImage->GetBlue(i+2,j) ;
            v4 = loadedImage->GetBlue(i, j+1) ;
            v5 = loadedImage->GetBlue(i+1, j+1) ;
            v6 = loadedImage->GetBlue(i+2, j+1);
            v7 = loadedImage->GetBlue(i, j+2) ;
            v8 = loadedImage->GetBlue(i+1, j+2) ;
            v9 = loadedImage->GetBlue(i+2, j+2) ;
//add m1 to m9, then divide by 9. that'll be average

            int bluearray[9] = {m1,m2,m3,m4,m5,m6,m7,m8,m9};

            for(int z = 0; z<9; z++)
            {
                if (bluearray[z]>tempblue)
                    tempblue=bluearray[z];
            }



            averagesumblue[i][j] = tempblue;

        }


	for(int i=0; i<imgWidth; i++)
	{

        for(int j=0; j<imgHeight; j++)
        {
            if(averagesumred[i][j]<0)
            {
                averagesumred[i][j] = 0;
            }
            if(averagesumred[i][j]>255)
            {
                averagesumred[i][j] = 255;
            }
            if(averagesumgreen[i][j]<0)
            {
                averagesumgreen[i][j] = 0;
            }
            if(averagesumgreen[i][j]>255)
            {
                averagesumgreen[i][j] = 255;
            }
            if(averagesumblue[i][j]<0)
            {
                averagesumblue[i][j] = 0;
            }
            if(averagesumblue[i][j]>255)
            {
                averagesumblue[i][j] = 255;
            }



            loadedImage->SetRGB(i,j,averagesumred[i][j],averagesumgreen[i][j],averagesumblue[i][j]);
        }
	}


    printf(" Finished max filtering.\n");

    Refresh();



}

//lab6 exercise 3 minfiltering
void MyFrame::MinFiltering(wxCommandEvent & event){
    printf("Min Filtering...");
    free(loadedImage);
    loadedImage = new wxImage(bitmap.ConvertToImage());
	int r,g,b;
	int m1,n1,v1;
	int m2,n2,v2;
	int m3,n3,v3;
	int m4,n4,v4;
	int m5,n5,v5;
	int m6,n6,v6;
	int m7,n7,v7;
	int m8,n8,v8;
	int m9,n9,v9;
	int counterr = 0;
	int counterb = 0;
	int counterg = 0;
    int averagesumred [imgWidth][imgHeight];
    int averagesumgreen [imgWidth][imgHeight];
    int averagesumblue [imgWidth][imgHeight];
    int mask [3][3];


    //mask multiplying by values on the image
	for(int i=0; i<imgWidth-1; i++)
        for(int j=0; j<imgHeight-1; j++)
        {

            int tempred = 255;
            int tempgreen = 255;
            int tempblue = 255;

            m1 = loadedImage->GetRed(0+i,0+j) ;
            m2 = loadedImage->GetRed(1+i,j) ;
            m3 = loadedImage->GetRed(2+i,j) ;
            m4 = loadedImage->GetRed(0+i, 1+j) ;
            m5 = loadedImage->GetRed(1+i, 1+j) ;
            m6 = loadedImage->GetRed(i+2, 1+j);
            m7 = loadedImage->GetRed(i+0, j+2) ;
            m8 = loadedImage->GetRed(i+1, j+2) ;
            m9 = loadedImage->GetRed(i+2, j+2) ;

            int redarray[9] = {m1,m2,m3,m4,m5,m6,m7,m8,m9};

            for(int z = 0; z<9; z++)
            {
                if (redarray[z]<tempred)
                    tempred=redarray[z];
            }

//add m1 to m9, then divide by 16 multiply all by weighted average. that'll be average

            averagesumred[i][j] = tempred;
//green

            n1 = loadedImage->GetGreen(i,j) ;
            n2 = loadedImage->GetGreen(i+1,j) ;
            n3 = loadedImage->GetGreen(i+2,j) ;
            n4 = loadedImage->GetGreen(i, j+1) ;
            n5 = loadedImage->GetGreen(i+1, j+1) ;
            n6 = loadedImage->GetGreen(i+2, j+1);
            n7 = loadedImage->GetGreen(i, j+2) ;
            n8 = loadedImage->GetGreen(i+1, j+2) ;
            n9 = loadedImage->GetGreen(i+2, j+2) ;
//add m1 to m9, then divide by 9. that'll be average

            int greenarray[9] = {m1,m2,m3,m4,m5,m6,m7,m8,m9};

            for(int z = 0; z<9; z++)
            {
                if (greenarray[z]<tempgreen)
                    tempgreen=greenarray[z];
            }

            averagesumgreen[i][j] = tempgreen;
//blue

            v1 = loadedImage->GetBlue(i,j) ;
            v2 = loadedImage->GetBlue(i+1,j) ;
            v3 = loadedImage->GetBlue(i+2,j) ;
            v4 = loadedImage->GetBlue(i, j+1) ;
            v5 = loadedImage->GetBlue(i+1, j+1) ;
            v6 = loadedImage->GetBlue(i+2, j+1);
            v7 = loadedImage->GetBlue(i, j+2) ;
            v8 = loadedImage->GetBlue(i+1, j+2) ;
            v9 = loadedImage->GetBlue(i+2, j+2) ;
//add m1 to m9, then divide by 9. that'll be average

            int bluearray[9] = {m1,m2,m3,m4,m5,m6,m7,m8,m9};

            for(int z = 0; z<9; z++)
            {
                if (bluearray[z]<tempblue)
                    tempblue=bluearray[z];
            }

            averagesumblue[i][j] = tempblue;

        }


	for(int i=0; i<imgWidth; i++)
	{

        for(int j=0; j<imgHeight; j++)
        {
            if(averagesumred[i][j]<0)
            {
                averagesumred[i][j] = 0;
            }
            if(averagesumred[i][j]>255)
            {
                averagesumred[i][j] = 255;
            }
            if(averagesumgreen[i][j]<0)
            {
                averagesumgreen[i][j] = 0;
            }
            if(averagesumgreen[i][j]>255)
            {
                averagesumgreen[i][j] = 255;
            }
            if(averagesumblue[i][j]<0)
            {
                averagesumblue[i][j] = 0;
            }
            if(averagesumblue[i][j]>255)
            {
                averagesumblue[i][j] = 255;
            }



            loadedImage->SetRGB(i,j,averagesumred[i][j],averagesumgreen[i][j],averagesumblue[i][j]);
        }
	}

    // cout<<arraycount;

    printf(" Finished min filtering.\n");

    Refresh();

}

//lab6 exercise 4 midpoint filtering
void MyFrame::MidFiltering(wxCommandEvent & event){
    printf("Midpoint Filtering...");
    free(loadedImage);
    loadedImage = new wxImage(bitmap.ConvertToImage());
	int r,g,b;
	int m1,n1,v1;
	int m2,n2,v2;
	int m3,n3,v3;
	int m4,n4,v4;
	int m5,n5,v5;
	int m6,n6,v6;
	int m7,n7,v7;
	int m8,n8,v8;
	int m9,n9,v9;
	int counterr = 0;
	int counterb = 0;
	int counterg = 0;
    int averagesumred [imgWidth][imgHeight];
    int averagesumgreen [imgWidth][imgHeight];
    int averagesumblue [imgWidth][imgHeight];
    int mask [3][3];


    //mask multiplying by values on the image
	for(int i=0; i<imgWidth-1; i++)
        for(int j=0; j<imgHeight-1; j++)
        {

            int lowred = 0;
            int lowgreen = 0;
            int lowblue = 0;
            int highred = 255;
            int highgreen = 255;
            int highblue = 255;

            m1 = loadedImage->GetRed(0+i,0+j) ;
            m2 = loadedImage->GetRed(1+i,j) ;
            m3 = loadedImage->GetRed(2+i,j) ;
            m4 = loadedImage->GetRed(0+i, 1+j) ;
            m5 = loadedImage->GetRed(1+i, 1+j) ;
            m6 = loadedImage->GetRed(i+2, 1+j);
            m7 = loadedImage->GetRed(i+0, j+2) ;
            m8 = loadedImage->GetRed(i+1, j+2) ;
            m9 = loadedImage->GetRed(i+2, j+2) ;

            int redarray[9] = {m1,m2,m3,m4,m5,m6,m7,m8,m9};

            for(int z = 0; z<9; z++)
            {
                if (redarray[z]>lowred)
                    lowred=redarray[z];
            }

            for(int z = 0; z<9; z++)
            {
                if (redarray[z]<highred)
                    highred=redarray[z];
            }



//add m1 to m9, then divide by 16 multiply all by weighted average. that'll be average

            averagesumred[i][j] = (highred + lowred)/2;
//green


            n1 = loadedImage->GetGreen(i,j) ;
            n2 = loadedImage->GetGreen(i+1,j) ;
            n3 = loadedImage->GetGreen(i+2,j) ;
            n4 = loadedImage->GetGreen(i, j+1) ;
            n5 = loadedImage->GetGreen(i+1, j+1) ;
            n6 = loadedImage->GetGreen(i+2, j+1);
            n7 = loadedImage->GetGreen(i, j+2) ;
            n8 = loadedImage->GetGreen(i+1, j+2) ;
            n9 = loadedImage->GetGreen(i+2, j+2) ;
//add m1 to m9, then divide by 9. that'll be average

            int greenarray[9] = {m1,m2,m3,m4,m5,m6,m7,m8,m9};

            for(int z = 0; z<9; z++)
            {
                if (greenarray[z]>lowgreen)
                    lowgreen=greenarray[z];
            }

            for(int z = 0; z<9; z++)
            {
                if (greenarray[z]<highgreen)
                    highgreen=greenarray[z];
            }



            averagesumgreen[i][j] = (highgreen+lowgreen)/2;
//blue

            v1 = loadedImage->GetBlue(i,j) ;
            v2 = loadedImage->GetBlue(i+1,j) ;
            v3 = loadedImage->GetBlue(i+2,j) ;
            v4 = loadedImage->GetBlue(i, j+1) ;
            v5 = loadedImage->GetBlue(i+1, j+1) ;
            v6 = loadedImage->GetBlue(i+2, j+1);
            v7 = loadedImage->GetBlue(i, j+2) ;
            v8 = loadedImage->GetBlue(i+1, j+2) ;
            v9 = loadedImage->GetBlue(i+2, j+2) ;
//add m1 to m9, then divide by 9. that'll be average

            int bluearray[9] = {m1,m2,m3,m4,m5,m6,m7,m8,m9};

            for(int z = 0; z<9; z++)
            {
                if (bluearray[z]>lowblue)
                    lowblue=bluearray[z];
            }

            for(int z = 0; z<9; z++)
            {
                if (bluearray[z]<highblue)
                    highblue=bluearray[z];
            }




            averagesumblue[i][j] = (highblue + lowblue)/2;

        }


	for(int i=0; i<imgWidth; i++)
	{

        for(int j=0; j<imgHeight; j++)
        {
            if(averagesumred[i][j]<0)
            {
                averagesumred[i][j] = 0;
            }
            if(averagesumred[i][j]>255)
            {
                averagesumred[i][j] = 255;
            }
            if(averagesumgreen[i][j]<0)
            {
                averagesumgreen[i][j] = 0;
            }
            if(averagesumgreen[i][j]>255)
            {
                averagesumgreen[i][j] = 255;
            }
            if(averagesumblue[i][j]<0)
            {
                averagesumblue[i][j] = 0;
            }
            if(averagesumblue[i][j]>255)
            {
                averagesumblue[i][j] = 255;
            }


            loadedImage->SetRGB(i,j,averagesumred[i][j],averagesumgreen[i][j],averagesumblue[i][j]);
        }
	}


    printf(" Finished min filtering.\n");

    Refresh();


}

///lab6 exercise 5 medianfiltering
void MyFrame::MedFiltering(wxCommandEvent & event){}
//###########################################################//
//-----------------------------------------------------------//
//---------- LAB7 -------------------
//-----------------------------------------------------------//
//###########################################################//

//Negative Linear Transform
void MyFrame::Negative(wxCommandEvent & event){

    free(loadedImage);
    loadedImage = new wxImage(bitmap.ConvertToImage());

    for( int i=0;i<imgWidth;i++)
        for(int j=0;j<imgHeight;j++){
            loadedImage->SetRGB(i,j,255-loadedImage->GetRed(i,j),
                                255-loadedImage->GetGreen(i,j),
                                255-loadedImage->GetBlue(i,j));
        }

    printf(" Finished  negative linear transform.\n");
    Refresh();
}

//Logarithmic function

void MyFrame::Logarithmic(wxCommandEvent & event){

    printf("log function...");
    free(loadedImage);
    loadedImage = new wxImage(bitmap.ConvertToImage());

	int r,g,b;
	int sumr,sumg,sumb;
	int constant;
    cout<<"\nEnter user constant:\n";
    cin>> constant;




    for( int i=0;i<imgWidth;i++)
        for(int j=0;j<imgHeight;j++){

            r = loadedImage -> GetRed(i,j);
            g = loadedImage -> GetGreen(i,j);
            b = loadedImage -> GetBlue(i,j);

            sumr = constant * log(1+r);
            sumg = constant * log(1+g);
            sumb = constant * log(1+b);


            loadedImage->SetRGB(i,j,sumr,sumg,sumb);
        }

    printf("\n\nFinished log function.\n");
    Refresh();

}

void MyFrame::PowerLaw(wxCommandEvent & event){

    printf("log function...");
    free(loadedImage);
    loadedImage = new wxImage(bitmap.ConvertToImage());

	float r,g,b;
	float sumr,sumg,sumb;
	float constant;
	float power;
    cout<<"\nEnter user constant:\n";
    cin>> constant;

    float random_number = (rand () % 2501/100);

    cout<< "\nRandom Power between 0.01 and 25 is" << random_number ;


    for( int i=0;i<imgWidth;i++)
        for(int j=0;j<imgHeight;j++){

            r = loadedImage -> GetRed(i,j);
            g = loadedImage -> GetGreen(i,j);
            b = loadedImage -> GetBlue(i,j);

            sumr = constant * pow(r,random_number);
            sumg = constant * pow(g,random_number);
            sumb = constant * pow(b,random_number);


            loadedImage->SetRGB(i,j,sumr,sumg,sumb);
        }

    printf("\n\nFinished log function.\n");
    Refresh();

}






void MyFrame::RandomLookUp(wxCommandEvent & event){


    printf("random lookup function...");
    free(loadedImage);
    loadedImage = new wxImage(bitmap.ConvertToImage());

	int r,g,b;
	float sumr,sumg,sumb;
	float constant;
	float power;
	int newArray[255];
    //float random_number = (rand () % 256);

	for( int z = 0; z<255; z++)
	{
        newArray[z] = (rand () % 256);
	}


    for(int i=0;i<imgWidth;i++)
        for(int j=0;j<imgHeight;j++){

            r = loadedImage -> GetRed(i,j);
            g = loadedImage -> GetGreen(i,j);
            b = loadedImage -> GetBlue(i,j);
            int newRed = newArray[r];
            int newGreen = newArray[g];
            int newBlue = newArray[b];


//	sumr = constant * pow(r,random_number);
//	sumg = constant * pow(g,random_number);
//	sumb = constant * pow(b,random_number);


            loadedImage->SetRGB(i,j,newRed,newGreen,newBlue);
        }

    printf("\n\nFinished random lookup function.\n");
    Refresh();


}



void MyFrame::FindHistogram(wxCommandEvent & event){

    printf("Finding  Histogram of image...");
    free(loadedImage);
    loadedImage = new wxImage(bitmap.ConvertToImage());

	int r,g,b;
	float rArray[256];
	float gArray[256];
	float bArray[256];


    for(int z=0;z<256;z++) {
        rArray[z] = 0;
        gArray[z] = 0;
        bArray[z] = 0;
    }


    for(int i=0;i<imgWidth;i++) {
        for(int j=0;j<imgHeight;j++){

			r = loadedImage -> GetRed(i,j);
			g = loadedImage -> GetGreen(i,j);
			b = loadedImage -> GetBlue(i,j);

			rArray[r] ++;
			gArray[g] ++;
			bArray[b] ++;

			//cout << r << endl;

        }
	}

    printf("Found Histogram!");

/* /////////////////////////////////////////////////////// */
/* Normalize now! */
/* /////////////////////////////////////////////////////// */

    float res = imgWidth * imgHeight;

	for(int y = 0;y<256;y++) {
		rArray[y] = rArray[y] / res;
		gArray[y] = gArray[y] / res;
		bArray[y] = bArray[y] / res;
	}


/* /////////////////////////////////////////////////////// */
/* Equalize now! */
/* /////////////////////////////////////////////////////// */

    float rCDF[256],gCDF[256],bCDF[256];
	rCDF[0] = rArray[0];
	gCDF[0] = gArray[0];
	bCDF[0] = bArray[0];
	for(int x=1;x<256;x++) {
		rCDF[x] = rCDF[x-1] + rArray[x];
		gCDF[x] = gCDF[x-1] + gArray[x];
		bCDF[x] = bCDF[x-1] + bArray[x];
	}


	for(int i=0;i<imgWidth;i++)
        for(int j=0;j<imgHeight;j++){
            loadedImage->SetRGB(i,j,rCDF[loadedImage->GetRed(i,j)]*255,
                                gCDF[loadedImage->GetGreen(i,j)]*255,
                                bCDF[loadedImage->GetBlue(i,j)]*255);
        }

	printf("\n\nFinished histogram equalisation function.\n");
	Refresh();
}

void MyFrame::HistogramMean(wxCommandEvent & event){
    printf("Finding  Histogram of image...");
    free(loadedImage);
    loadedImage = new wxImage(bitmap.ConvertToImage());

	int r,g,b;
	float rArray[256];
	float gArray[256];
	float bArray[256];


    for(int z=0;z<256;z++) {
        rArray[z] = 0;
        gArray[z] = 0;
        bArray[z] = 0;
    }


    for(int i=0;i<imgWidth;i++) {
        for(int j=0;j<imgHeight;j++){

			r = loadedImage -> GetRed(i,j);
			g = loadedImage -> GetGreen(i,j);
			b = loadedImage -> GetBlue(i,j);

			rArray[r] ++;
			gArray[g] ++;
			bArray[b] ++;

			//cout << r << endl;

        }
	}

    printf("Found Histogram!");

/* /////////////////////////////////////////////////////// */
/* Normalize now! */
/* /////////////////////////////////////////////////////// */

    float res = imgWidth * imgHeight;
    float rSum,gSum,bSum = 0;

    for(int i=0;i<256;i++) {
        rSum += rArray[i] * i;
        gSum += gArray[i] * i;
        bSum += bArray[i] * i;
    }

    cout << "Red's Histogram mean is: " << (rSum/res) << endl;
    cout << "Green's Histogram mean is: " << (gSum/res) << endl;
    cout << "Blue's Histogram mean is: " << (bSum/res) << endl;

}

void MyFrame::HistogramSD(wxCommandEvent & event){
    printf("Finding  Histogram of image...");
    free(loadedImage);
    loadedImage = new wxImage(bitmap.ConvertToImage());

	int r,g,b;
	float rArray[256];
	float gArray[256];
	float bArray[256];


    for(int z=0;z<256;z++) {
        rArray[z] = 0;
        gArray[z] = 0;
        bArray[z] = 0;
    }


    for(int i=0;i<imgWidth;i++) {
        for(int j=0;j<imgHeight;j++){

			r = loadedImage -> GetRed(i,j);
			g = loadedImage -> GetGreen(i,j);
			b = loadedImage -> GetBlue(i,j);

			rArray[r] ++;
			gArray[g] ++;
			bArray[b] ++;

			//cout << r << endl;

        }
    }

    printf("Found Histogram!");

    float res = imgWidth * imgHeight;
    float rSum,gSum,bSum = 0;

    for(int i=0;i<256;i++) {
	    rSum += rArray[i] * i;
	    gSum += gArray[i] * i;
	    bSum += bArray[i] * i;
    }
    float rMean = rSum/res;
    float gMean = gSum/res;
    float bMean = bSum/res;

    float rSqArray[256];
    float gSqArray[256];
    float bSqArray[256];
    float rvar_sum,gvar_sum,bvar_sum = 0;

    for(int i=0;i<imgWidth;i++) {
	    for(int j=0;j<imgHeight;j++){

		    r = loadedImage -> GetRed(i,j);
		    g = loadedImage -> GetGreen(i,j);
		    b = loadedImage -> GetBlue(i,j);
		    rvar_sum += pow(r-rMean,2);
		    gvar_sum += pow(g-gMean,2);
		    bvar_sum += pow(b-bMean,2);
		    //cout << r << endl;

	    }
    }

    float rvar = rvar_sum/res;
    float gvar = gvar_sum/res;
    float bvar = bvar_sum/res;

    float rStd = sqrt(rvar);
    float gStd = sqrt(gvar);
    float bStd = sqrt(bvar);

    cout << "Red Standard Deviation: " << rStd << endl;
    cout << "Green Standard Deviation: " << gStd << endl;
    cout << "Blue Standard Deviation: " << bStd << endl;

}
void MyFrame::SimpleThresholding(wxCommandEvent & event){
	int user_threshold_val;
	int overwrite_val = 255;
	cout << "\n Please enter your threshold value: " << endl;
	cin >> user_threshold_val;
	free(loadedImage);
	loadedImage = new wxImage(bitmap.ConvertToImage());
	int r,g,b;

	int greyscale;

	for( int i=0;i<imgWidth;i++)
		for(int j=0;j<imgHeight;j++){

			r = loadedImage -> GetRed(i,j);
			g = loadedImage -> GetGreen(i,j);
			b = loadedImage -> GetBlue(i,j);
			greyscale = (r+g+b)/3;
			//Overwrite rgb values if over threshold.
			if(greyscale>user_threshold_val){greyscale=overwrite_val;}
			else{greyscale=0;}
			loadedImage->SetRGB(i,j,greyscale,greyscale,greyscale);
		}

	printf("\n\nFinished simple threshold function.\n");
	Refresh();

}

void MyFrame::AutomatedThresholding(wxCommandEvent & event){

	free(loadedImage);
	loadedImage = new wxImage(bitmap.ConvertToImage());
	int r,g,b;
	int num_of_white,num_of_black;
	int greyscale;
	float original_threshold = 127;
	float current_threshold;
	float new_threshold;
	current_threshold = original_threshold;
	float white_sum,black_sum=0;

	for( int i=0;i<imgWidth;i++)
		for(int j=0;j<imgHeight;j++){

			r = loadedImage -> GetRed(i,j);
			g = loadedImage -> GetGreen(i,j);
			b = loadedImage -> GetBlue(i,j);
			greyscale = (r+g+b)/3;
			if(greyscale < current_threshold){black_sum+=greyscale;num_of_black++;}
			else{white_sum+=greyscale;num_of_white++;}
			new_threshold = ((white_sum/num_of_white) + (black_sum/num_of_black))/2;
			if((new_threshold-current_threshold)<original_threshold) {
				break;
			}
			else {
				current_threshold=new_threshold;
				if(greyscale<current_threshold){greyscale=0;}
				else{greyscale=255;}
			}
			loadedImage->SetRGB(i,j,greyscale,greyscale,greyscale);
		}

	printf("\nFinished iterative automated threshold function.\n");
	Refresh();

}

//###########################################################//
//-----------------------------------------------------------//
//---------- DO NOT MODIFY THE CODE BELOW--------------------//
//-----------------------------------------------------------//
//###########################################################//


//IMAGE SAVING
void MyFrame::OnSaveImage(wxCommandEvent & event){

	printf("Saving image...");
	free(loadedImage);
	loadedImage = new wxImage(bitmap.ConvertToImage());

	loadedImage->SaveFile(wxT("Saved_Image.bmp"), wxBITMAP_TYPE_BMP);

	printf("Finished Saving.\n");
}

void MyFrame::OnRawOpenFile(wxCommandEvent & event) {
    wxFileDialog *openFileDialog = new wxFileDialog ( this, _T("Open file"), _T(""), _T(""), FILETYPES, wxOPEN, wxDefaultPosition);
    if(openFileDialog->ShowModal() == wxID_OK){
        wxString filename = openFileDialog->GetFilename();
        wxString path = openFileDialog->GetPath();
        printf("Loading raw image form file...");

        int size = 0;
        FILE* pInput = NULL;
        unsigned char* buf;
        unsigned char* nbuf;

        if (pInput = fopen(path.char_str(), "r")){
            fseek(pInput,0,SEEK_END);
            size = ftell(pInput);
            fseek(pInput,0,SEEK_SET);
            buf = new unsigned char[size];
            nbuf = new unsigned char[size*3];
            fread(buf,sizeof(char),size,pInput);
        }

        int ii=0;
        int j = 0;
        for( int i = 0; i < (size) *3; i=i+3 )
        {
            nbuf[i]=buf[ii];
            nbuf[i+1]=buf[ii];
            nbuf[i+2]=buf[ii];
            ii=ii+1;
        }

        loadedImage = new wxImage(sqrt(size),sqrt(size),nbuf,false);
        if(loadedImage->Ok()){
            stuffToDraw = ORIGINAL_IMG;    // set the display flag
            printf("Done! \n");
        }
        Refresh();
    }
}



void MyFrame::OnExit (wxCommandEvent & event){
	Close(TRUE);
}


void MyFrame::OnPaint(wxPaintEvent & event){
	wxPaintDC dc(this);
	int cWidth, cHeight;
	GetSize(&cWidth, &cHeight);
	if ((back_bitmap == NULL) || (oldWidth != cWidth) || (oldHeight != cHeight)) {
		if (back_bitmap != NULL)
			delete back_bitmap;
		back_bitmap = new wxBitmap(cWidth, cHeight);
		oldWidth = cWidth;
		oldHeight = cHeight;
	}
	wxMemoryDC *temp_dc = new wxMemoryDC(&dc);
	temp_dc->SelectObject(*back_bitmap);
	// We can now draw into the offscreen DC...
	temp_dc->Clear();
	if(loadedImage)
		temp_dc->DrawBitmap(wxBitmap(*loadedImage), 0, 0, false);//given bitmap xcoord y coord and transparency

	switch(stuffToDraw){
		case NOTHING:
			break;
		case ORIGINAL_IMG:
			bitmap.CleanUpHandlers; // clean the actual image header
			bitmap = wxBitmap(*loadedImage); // Update the edited/loaded image
			break;
	}

	// update image size
	imgWidth  = (bitmap.ConvertToImage()).GetWidth();
	imgHeight = (bitmap.ConvertToImage()).GetHeight();



	temp_dc->SelectObject(bitmap);//given bitmap

	//end draw all the things
	// Copy from this DC to another DC.
	dc.Blit(0, 0, cWidth, cHeight, temp_dc, 0, 0);
	delete temp_dc; // get rid of the memory DC
}

	BEGIN_EVENT_TABLE (MyFrame, wxFrame)
	EVT_MENU ( LOAD_FILE_ID,  MyFrame::OnOpenFile)
	EVT_MENU ( RAWLOAD_FILE_ID,  MyFrame::OnRawOpenFile)
    EVT_MENU ( EXIT_ID,  MyFrame::OnExit)

	//###########################################################//

	//###########################################################//

	EVT_MENU ( INVERT_IMAGE_ID,  MyFrame::OnInvertImage)
	EVT_MENU ( SCALE_IMAGE_ID,  MyFrame::OnScaleImage)
	EVT_MENU ( SAVE_IMAGE_ID,  MyFrame::OnSaveImage)
	EVT_MENU ( SHIFTING_IMAGE_ID,  MyFrame::Shifting)
	EVT_MENU ( AVERAGING_IMAGE_ID,  MyFrame::Averaging)
	EVT_MENU ( WEIGHTED_IMAGE_ID,  MyFrame::Weighted)
	EVT_MENU ( FLAPLACIAN_IMAGE_ID,  MyFrame::FLaplacian)
	EVT_MENU ( ELAPLACIAN_IMAGE_ID,  MyFrame::ELaplacian)
	EVT_MENU ( FLAPLACIANE_IMAGE_ID,  MyFrame::FLaplacianE)
	EVT_MENU ( ELAPLACIANE_IMAGE_ID,  MyFrame::ELaplacianE)
	EVT_MENU ( ROBERTS_IMAGE_ID,  MyFrame::Roberts)
	EVT_MENU ( SOBELX_IMAGE_ID,  MyFrame::Sobelx)
	EVT_MENU ( SOBELY_IMAGE_ID,  MyFrame::Sobely)
	EVT_MENU ( SALTANDPEPPER_IMAGE_ID,  MyFrame::SaltandPepperFiltering)
	EVT_MENU ( MINFILTERING_IMAGE_ID,  MyFrame::MinFiltering)//--->To be modified!
	EVT_MENU ( MAXFILTERING_IMAGE_ID,  MyFrame::MaxFiltering)
	EVT_MENU ( MIDPOINTFILTERING_IMAGE_ID,  MyFrame::MidFiltering)
	EVT_MENU ( MEDIANFILTERING_IMAGE_ID,  MyFrame::MedFiltering)
	EVT_MENU ( NEGATIVE_IMAGE_ID,  MyFrame::Negative)
	EVT_MENU ( LOGARITHMIC_IMAGE_ID,  MyFrame::Logarithmic)
	EVT_MENU ( POWERLAW_IMAGE_ID,  MyFrame::PowerLaw)
	EVT_MENU ( RANDOMLOOKUP_IMAGE_ID,  MyFrame::RandomLookUp)
    EVT_MENU ( UNDO_IMAGE_ID,  MyFrame::UndoImage)
// EVT_MENU ( ROI_IMAGE_ID,  MyFrame::ROI)
	EVT_MENU ( RESCALE_IMAGE_ID,  MyFrame::Rescale)
	EVT_MENU ( HISTOGRAM_IMAGE_ID, MyFrame::FindHistogram)
	EVT_MENU ( MEAN_IMAGE_ID, MyFrame::HistogramMean)
	EVT_MENU ( STANDARDDEVIATION_IMAGE_ID, MyFrame::HistogramSD)
	EVT_MENU ( STHRESHOLDING_IMAGE_ID, MyFrame::SimpleThresholding)
    EVT_MENU ( ATHRESHOLDING_IMAGE_ID, MyFrame::AutomatedThresholding)


	//###########################################################//
	//----------------------END MY EVENTS -----------------------//
	//###########################################################//

	EVT_PAINT (MyFrame::OnPaint)
END_EVENT_TABLE()
