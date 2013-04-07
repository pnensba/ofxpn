#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxMacamPs3Eye.h"

//#include <opencv/cv.h>
//#include <assert.h>

#define _USE_LIVE_VIDEO		// uncomment this to use a live camera
								// otherwise, we'll use a movie file
#define CV_USE_VIDEO 0
#define CV_USE_LIVE_VIDEO 1
#define CV_USE_PICTURE	2

#define CV_MODE_DEV 1
#define CV_MODE_USR 1

enum MENU_MODE { MENU_MAIN, MENU_SETTING, MENU_LETTER };

typedef struct {
	CvBox2D box;
	char str[15];
} button_box;

typedef struct {
	button_box *box_list;
	int n;
} button_box_collection;

typedef struct {
	int n;
	CvPoint2D32f *v;
} fLUT;

typedef struct {
	int cur;
	int tot;
} frame_counter;

typedef struct {
	int mode;
	//ofVideoGrabber vg;
    ofxMacamPs3Eye vg;
	ofVideoPlayer  vp;
	bool ready;
} video_context;

/*
 * A struct.
 */
typedef struct {
	CvPoint		selected;///< Stores which point is currently selected (for data entry)
	int rows;///< Number of rows in calibration structure.
	int cols;///< Number of columns in calibration structure.
	CvMat *src_mat;
	CvMat *dst_mat;
	///< Holds source points (uncalibrated gaze points)
	///< Holds destination points (predetermined screen points)
	CvMat		 **mat;///< Holds derived projection transformation matrices.
} calibration_datum;

typedef struct {
	CvPoint a;
	CvPoint b;
	CvPoint c;
	int matidx;
}lookup_entry;

class cvEyeTracker : public ofBaseApp{

	public:
	void setup();
	void update();
	void draw();
	
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	
	void initVars();
	
	void initEnvironment( CvSize the_size );
	void initFrameBuffer( CvSize the_size );
	
	bool getFrame( IplImage *ipl_csrc );	
	
	bool initVideo( video_context *vid_context,
				   frame_counter *counter,
				   CvSize *size );
	int xy2idx( int x, int y, int w );
	// update/draw Histogram
	void calcHistogramROI( IplImage *img_in, CvHistogram *hist_out, CvRect the_roi );
	void calcHistogramMask( IplImage *img_in, CvHistogram *hist_out, IplImage *mask_in );
	void drawHistogram(float *fake_hist, IplImage *img);	
	///< Draw a histogram (float array) into an IplImage.
	
	CvPoint2D32f calcPupilOffset( float pupil_size, float angle_offset );
	
	bool findPupil(IplImage *img_in,
				   int thresh_in,
				   int flood_stop,
				   CvBox2D *ellipse_out,
				   CvRect *bbox_out );
	///< Find the pupil as an ellipse.
	
	bool findPerkinje( IplImage *img_in, CvPoint2D32f seed_pt, CvSeq* found_pt );
	///< Find perkinje rections and order them consistently.
	
	// load/query pupil decentration data
	void getPupilOffset( float _px, float *_offx, float*_offy );
	bool loadLUT();
	
	// update mapping data
	void calcPerspectiveMap( CvSeq *src_seq, CvSeq *dst_seq, CvMat* map_mat);
	///< Macro for calculating perspective transform from two CvSeq structures.
	
	// initialize a calibration map structure
	void initCalibrationMap(calibration_datum *new_map, int r, int c);
	///< Initialize a calibration map of a given size.
	
	void queryCalibrationMap( CvPoint2D32f query_pt, CvPoint2D32f *res_pt );
	///< Transform a point into calibrated screen space.
	
	void calcCalibrationMap(calibration_datum *new_map);
	
	// query the automatic pupil threshold
	
	void calcHistPeak( float *pupil_hist, float *iris_hist, int *peak, int *valley );
	///< Calculate the automatic threshold value from two histograms.
	
	fLUT newfLUT(int n);
	///< Create a new lookup table data object.
	float queryLUT( fLUT *qlut, float qv );
	///< Look up a y/range value from a given x/domain value. 
	int checkPoly( CvPoint2D32f P, CvPoint2D32f *V, int n );
	///< Check inclusion of a point against a polygon.
	void whichMat( CvPoint2D32f query_pt, calibration_datum D, CvPoint* S );
	///< Find which matrix transformation needs to be used for a given point.
	
	// text entry interfaces
	void drawLetterBoard();
	char **letterboard_row;
	
	// unused methods
	bool findHeadPoints( IplImage *img_in, CvPoint2D32f *found_pt );
	bool findRemoteEye( IplImage *img_in );
	
	int menumode;
	bool bNeedClick;
	
	// interpolation stuff
	
#define I_INTERP_N 2
#define I_INTERP_SCREEN 0
#define I_INTERP_HIST 1
	
	fLUT interp_arr[I_INTERP_N];
	
	fLUT *interp_lut;
	
#define MOVE_HIST_N 100
	float dwell_time;
	
	unsigned int last_move;
	
//	button_box_collection
	
	// stuff
	video_context cap_context;
	frame_counter cap_count;
	CvSize        cap_size;
	
	CvPoint last_match;
	
	calibration_datum calibration_map; 
	CvSize		cur_calib_pt;
	
	CvBox2D but_settings;
	CvBox2D but_letterboard;
	
	
	CvPoint2D32f cur_pupil_offset;
	
	CvRect       cur_roi;
	CvHistogram *hist_cur_src;
	CvHistogram *hist_roi_src;
	CvHistogram *hist_thresh_src;
	float      hist_cur[256];
	float      hist_avg[256];
	
	float      hist_roi[256];
	
	float      hist_roi_avg[256];
	float      hist_thresh_cur[256];
	float      hist_thresh_avg[256];
	
	
	float hist_cur_sum;
	float hist_pupil_sum;
	float hist_iris_sum;
	
	float hist_pupil[256];
	float hist_pupil_avg[256];
	float hist_iris[256];
	float hist_iris_avg[256];
	
	float      hist_maxv;
	float      h_max_v;
	int        threshold;
	int h_manual_threshold;
	
	CvPoint screen_forreal;
	CvPoint offset_center;
	
	CvPoint2D32f derp_pt;
	CvPoint2D32f center_pt;
	CvPoint2D32f pupil_current;
	CvPoint conjecture_pt;
		
	CvRect pupil_bbox;
	
	CvBox2D pupil_fit_cur;
	CvBox2D pupil_fit_avg;
	
	CvBox2D pupil_current_fit;
	float pupil_radius_avg;
	CvBox2D box_ellipse_fit;
	CvBox2D box_ellipse_avg;
	
	#define G_STOR_MAX 7
	CvMemStorage *g_storage[G_STOR_MAX];
	
	CvPoint2D32f perkinje_src_avg[4];
	CvSeq *perkinje_src_pts;
	CvSeq *perkinje_dst_pts;
	CvSeq *perkinje_tmp_pts;
	
	CvSeq *pk_tmp;
	CvSeq *fin_contour;
	CvSeq *seq_hull;
	
	CvConnectedComp pupil_ccomp;
	
	// mapping stuff
	CvMat			*persp_src_pt;
	CvMat			*persp_dst_pt;

	CvMat			*persp_src_3ch;
	CvMat			*persp_dst_3ch;
	
	CvMat			*persp_mat; // camera -> LED perspective map
	CvPoint2D32f	guess_pt;
	CvPoint2D32f	guess_pt_avg;
	CvPoint2D32f	screen_pt;
	CvPoint2D32f	screen_pt_avg;
	
	#define PK_TMP_N 50
	
	CvPoint2D32f perkinje_tmp_pos[PK_TMP_N];
	float perkinje_tmp_area[PK_TMP_N];
	float perkinje_tmp_dist[PK_TMP_N];
	int perkinje_tmp_n;
	
	int   h_cur_peak_val;
	int   h_cur_peak_idx;
	float h_avg_peak_val;
	float h_avg_peak_idx;
	
	int   h_cur_min_val;
	int   h_cur_min_idx;
	float h_avg_min_val;
	float h_avg_min_idx;
	
	int UIMODE;
	
	// defined names for image registers
	
#define I_ARR_N	 29

#define I_GRAY_0	0
#define I_GRAY_1	1
#define I_GRAY_2	2
#define I_GRAY_3	3
#define I_GTMP_0	4
#define I_GTMP_1	5
#define I_GTMP_2	6
#define I_GSRC		7
#define I_GOUT_0	8
#define I_GOUT_1	9
#define I_GOUT_2	10

#define I_CHIST_0	11 // preset size
#define I_CHIST_1	12 // preset size
#define I_CHIST_2	26 // preset size

#define I_CTMP_0	13
#define I_CTMP_1	28
#define I_CSRC		14

#define I_GDEBUG	15 // size of window
#define I_CDEBUG	16 // size of window

#define I_GREC		17
#define I_CREC		18

#define I_GMASK		19
#define I_GTHRESH_0 20
#define I_GTHRESH_1 21
#define I_GTHRESH_2 22

#define I_GFILLMASK 27
//#define I_GSOBEL	22
#define I_GDIFF_0	23
#define I_GDIFF_1	24
#define I_GACC		25
	
	IplImage *ipl_arr[I_ARR_N];
	
	ofVideoGrabber 		vidGrabber;
	ofVideoPlayer 		vidPlayer;
			
	// openframeworks display images
	
	ofImage of_img0;
	
	ofImage of_gray_src;
	ofImage of_gray_out0;
	ofImage of_gray_out1;
	ofImage of_gray_out2;
	
	ofxCvColorImage			ofx_color_src;
	ofxCvColorImage			ofx_hist0;
	ofxCvColorImage			ofx_hist1;
	ofxCvColorImage			ofx_hist2;
	ofxCvColorImage			ofx_color_out0;
	ofxCvColorImage			ofx_color_out1;
	ofxCvColorImage			ofx_color_out2;
	
	ofxCvGrayscaleImage		ofx_gray_src;
	ofxCvGrayscaleImage		ofx_gray_out0;
	ofxCvGrayscaleImage		ofx_gray_out1;
	ofxCvGrayscaleImage		ofx_gray_out2;
		
	// various geometric variables
	int step_rdy;
	
	char reportStr[1024];
	ofTrueTypeFont myfont0;
	ofTrueTypeFont bigFont0;
	CvFont mycvfont0;
		
	#define N_PERKINJE_SEEK 10 // max number of reflections to sample
		
	// perkinje stuff
	
	// from pupil/led relative to estimated LED pos
	// from led pos guess to real screen
	
	CvPoint2D32f perkinje_pts_raw[N_PERKINJE_SEEK];		// raw
	CvPoint2D32f perkinje_org_pts[N_PERKINJE_SEEK];		// ordered
	CvPoint2D32f perkinje_org_pts_avg[N_PERKINJE_SEEK];	 // ordered average
	
	// boolean flags
	#define LUT_N 15 // todo: dynamically load LUT
	
	// boolean options
	bool bVideoReady;
	bool bUseEyeMouse;
	bool bToggleRec;
	bool bToggleRecRaw;
	bool bNewFrame;
	bool bNeedRefresh;
	bool bUseStep;
	bool bFlipOrientation;
	bool bMapReady;
	bool bUseLUT;
	bool bLUTLoaded;
	
	bool bPrintDev;
	
	bool bDrawEyeImage;
	bool bDrawDevScreen;
	bool bDrawCalibrationTargetPoints;
	bool bDrawCalibrationSourcePoints;
	
	bool bDrawScreenGuessPoint;
	bool bDrawScreenGazePoint;
	
	bool bDrawPerkinjePoints;
	bool bDrawPupilEllipse;

};

