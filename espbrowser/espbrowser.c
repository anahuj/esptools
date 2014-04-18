
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#include "/home/juhana/gtk2/include/gtk-2.0/gtk/gtk.h"

#include "mylib/image.h"
#include "mylib/filesdirs.h"

typedef struct {
  GtkWidget *topwindow;
  char *topwindowtitle;
  int topwindow_xsize;
  int topwindow_ysize;
  GtkWidget *button;
  GtkWidget *da;
  void *image;
  void *displayimage;
  void *tmpdisplayimage;
  int display_xsize;
  int display_ysize;
  GdkGC *image_gc;
  // Logarithmic zoom from 1:1 to, e.g., 1:20 with numzoomlevels steps.
  int numzoomlevels;
  int zoomlevel;
  float zoomscale;
  float xcenter;
  float ycenter;
  int centerx; // Center of the display image. 
  int centery;
  float imgcenterx; // Center of the image. Computed from the center.
  float imgcentery;
  float maxzoomscale;
  float scale;
  int moving;
  int movex;
  int movey;
  int movexstart;
  int moveystart;
  int movexprev;
  int moveyprev;
  int movedx;
  int movedy;
  int isconfigure;
  GdkRgbDither dithertype;
  int dithx;
  int dithy;
  int numfiles;
  char **filenames;
  int currentfile;
  int scalingtype;
  // 0 = use p->scale
  // 1 = fit to window but do not enlarge
  // 2 = fit to window, enlarging allowed
  void *random;
  int rendertype; // 0 = single image, 1 = imagegraph
  void *imagegraph;
  int moveimageindex;
  void *nifrender;
#if 0
  float zscr;
  float back;
  float spin;
#endif
  float fillfactor;
  float movefillfactor;
  float move_start_zscr;
} ty_espbrowser;



#if 0

#include "mylib/image.h"
#include "mylib/filesdirs.h"
#include "mylib/clock.h"
// #include "mylib/random.h"
// random.h includes gsl_taus.c which makes this GPL software


typedef struct {
  float xmin;
  float ymin;
  float xmax;
  float ymax;
} ty_bound;

typedef struct {
  char *filename;
  void *image;
  int xsize; // Image pointer may be NULL.
  int ysize;
  float scale;
} ty_lodimage;

#define C_GEOMETRYIMAGE_TYPE_CONTAINER 0
#define C_GEOMETRYIMAGE_TYPE_IMAGE 1
#define C_TILE_XSIZE 256
#define C_TILE_YSIZE 256

// Each image is represented as rectangular geometry.
// The geometric objects can be grabbed and moved.
typedef struct {
  char *filename;
  void *image;
  int xsize;
  int ysize;
  void **lodimages; // lodimages[0] is the original tile.
  int nummaxlodimages;
  int numlodimages;
  float xpos;
  float ypos;
  // float scale;
} ty_tileimage;

typedef struct {
  // Container.
  int nummaxtileimages;
  int numtileimages;
  void **tileimages;
  char *filename; // Original filename.
  int xsize;
  int ysize;
  float xpos;
  float ypos;
  float scale;
} ty_geometryimage;

// Simple array now, more complex graph later.
typedef struct {
  int numimages;
  int maximages;
  void **images;
  void **lodimages; // XXXX
  float xpos;
  float ypos;
  float scale;
} ty_imagegraph;

typedef struct {
  // unsigned char *buffer;
  // int buflen;
  // int bufloc;
  GtkWidget *topwindow;
  char *topwindowtitle;
  int topwindow_xsize;
  int topwindow_ysize;
  GtkWidget *button;
  GtkWidget *da;
  void *image;
  void *displayimage;
  void *tmpdisplayimage;
  int display_xsize;
  int display_ysize;
  GdkGC *image_gc;
  // Logarithmic zoom from 1:1 to, e.g., 1:20 with numzoomlevels steps.
  int numzoomlevels;
  int zoomlevel;
  float zoomscale;
  float xcenter;
  float ycenter;
  int centerx; // Center of the display image. 
  int centery;
  float imgcenterx; // Center of the image. Computed from the center.
  float imgcentery;
  float maxzoomscale;
  float scale;
  int moving;
  int movex;
  int movey;
  int movexstart;
  int moveystart;
  int movexprev;
  int moveyprev;
  int movedx;
  int movedy;
  int isconfigure;
  GdkRgbDither dithertype;
  int dithx;
  int dithy;
  int numfiles;
  char **filenames;
  int currentfile;
  int scalingtype;
  // 0 = use p->scale
  // 1 = fit to window but do not enlarge
  // 2 = fit to window, enlarging allowed
  void *random;
  int rendertype; // 0 = single image, 1 = imagegraph
  void *imagegraph;
  int moveimageindex;
  void *nifrender;
#if 0
  float zscr;
  float back;
  float spin;
#endif
  float fillfactor;
  float movefillfactor;
  float move_start_zscr;
} ty_viewer;

char cmd_send[200];
char cmd_return[200];


void *openimage(char *s)
{
  char *fn;
  void *image;

  fn = &(s[strlen(s)-4]);
  // fprintf(stderr,"fn = \"%s\"\n",fn); // prints ".png"
  if ((strcmp(fn,".png") == 0) || (strcmp(fn,".PNG") == 0)) {
    image = image_load_file_png(s);
  } else if ((strcmp(fn,".jpg") == 0) || (strcmp(fn,".JPG") == 0)) {
    image = image_load_file_jpeg(s);
  } else if ((strcmp(fn,".ppm") == 0) || (strcmp(fn,".PPM") == 0)) {
    image = image_load_file(s);
  } else if ((strcmp(fn,".pgm") == 0) || (strcmp(fn,".PGM") == 0)) {
    image = image_load_file(s);
  } else if ((strcmp(fn,".pnm") == 0) || (strcmp(fn,".PNM") == 0)) {
    image = image_load_file(s);
  } else {
    // Check for ".jpeg".
    fn = &(s[strlen(s)-5]);
    if ((strcmp(fn,".jpeg") == 0) || (strcmp(fn,".JPEG") == 0)) {
      image = image_load_file_jpeg(s);
    } else {
      // Check for ".ppm.gz".
      fn = &(s[strlen(s)-7]);
      if ((strcmp(fn,".ppm.gz") == 0) || (strcmp(fn,".pgm.gz") == 0) || (strcmp(fn,".pnm.gz") == 0)) {
	image = image_load_file_comp(s);
      } else {
	fprintf(stderr,"unknown image type for %s\n",s);
	return NULL;
      }
    }
  }

  return image;
}

int checkimage(char *s)
{
  char *fn;

  fn = &(s[strlen(s)-4]);
  // fprintf(stderr,"fn = \"%s\"\n",fn); // prints ".png"
  if ((strcmp(fn,".png") == 0) || (strcmp(fn,".PNG") == 0)) {
    return 1;
  } else if ((strcmp(fn,".jpg") == 0) || (strcmp(fn,".JPG") == 0)) {
    return 1;
  } else if ((strcmp(fn,".ppm") == 0) || (strcmp(fn,".PPM") == 0)) {
    return 1;
  } else if ((strcmp(fn,".pgm") == 0) || (strcmp(fn,".PGM") == 0)) {
    return 1;
  } else if ((strcmp(fn,".pnm") == 0) || (strcmp(fn,".PNM") == 0)) {
    return 1;
  } else {
    // Check for ".jpeg".
    fn = &(s[strlen(s)-5]);
    if ((strcmp(fn,".jpeg") == 0) || (strcmp(fn,".JPEG") == 0)) {
      return 1;
    } else {
      // Check for ".ppm.gz".
      fn = &(s[strlen(s)-7]);
      if ((strcmp(fn,".ppm.gz") == 0) || (strcmp(fn,".pgm.gz") == 0) || (strcmp(fn,".pnm.gz") == 0)) {
	return 1;
      } else {
	fprintf(stderr,"unknown image type for %s\n",s);
	return 0;
      }
    }
  }

  return 0;
}

void *lodimage_new(char *s)
{
  ty_lodimage *p;

  p = (ty_lodimage *)malloc(sizeof(ty_lodimage));
  p->filename = s;
  p->image = NULL;
  p->xsize = -1;
  p->ysize = -1;
  p->scale = 1.0;

  return (void *)p;
}

void lodimage_set_size(void *pp, int xsize, int ysize)
{
  ty_lodimage *p;

  p = pp;
  p->xsize = xsize;
  p->ysize = ysize;
}

int lodimage_get_xsize(void *pp)
{
  ty_lodimage *p;

  p = pp;
  return p->xsize;
}

int lodimage_get_ysize(void *pp)
{
  ty_lodimage *p;

  p = pp;
  return p->ysize;
}

void *lodimage_get_image(void *pp)
{
  ty_lodimage *p;

  p = pp;
  return p->image;
}

void lodimage_set_image(void *pp, void *image)
{
  ty_lodimage *p;

  p = pp;
  p->image = image;
}

char *lodimage_get_filename(void *pp)
{
  ty_lodimage *p;

  p = pp;
  return p->filename;
}

void lodimage_set_scale(void *pp, float scale)
{
  ty_lodimage *p;

  p = pp;
  p->scale = scale;
}

float lodimage_get_scale(void *pp)
{
  ty_lodimage *p;

  p = pp;
  return p->scale;
}

void *tileimage_new(char *s)
{
  ty_tileimage *p;

  p = (ty_tileimage *)malloc(sizeof(ty_tileimage));
  p->filename = s;
  // p->image = NULL;
  p->xsize = -1;
  p->ysize = -1;
  p->nummaxlodimages = 10;
  p->lodimages = (void **)malloc(p->nummaxlodimages*sizeof(void *));
  p->numlodimages = 0;
  p->xpos = 0.0;
  p->xpos = 0.0;

  return (void *)p;
}

char *tileimage_get_filename(void *pp)
{
  ty_tileimage *p;

  p = pp;
  return p->filename;
}

void tileimage_set_size(void *pp, int xsize, int ysize)
{
  ty_tileimage *p;

  p = pp;
  p->xsize = xsize;
  p->ysize = ysize;
}

int tileimage_get_xsize(void *pp)
{
  ty_tileimage *p;

  p = pp;
  return p->xsize;
}

int tileimage_get_ysize(void *pp)
{
  ty_tileimage *p;

  p = pp;
  return p->ysize;
}

void tileimage_set_pos(void *pp, float xpos, float ypos)
{
  ty_tileimage *p;

  p = pp;
  p->xpos = xpos;
  p->ypos = ypos;
}

float tileimage_get_xpos(void *pp)
{
  ty_tileimage *p;

  p = pp;
  return p->xpos;
}

float tileimage_get_ypos(void *pp)
{
  ty_tileimage *p;

  p = pp;
  return p->ypos;
}

void tileimage_set_numlodimages(void *pp, int n)
{
  ty_tileimage *p;

  p = pp;
  p->numlodimages = n;
}

int tileimage_get_numlodimages(void *pp)
{
  ty_tileimage *p;

  p = pp;
  return p->numlodimages;
}

void tileimage_set_lodimage(void *pp, int n, void *li)
{
  ty_tileimage *p;

  p = pp;
  p->lodimages[n] = li;
}

void *tileimage_get_lodimage(void *pp, int n)
{
  ty_tileimage *p;

  p = pp;
  return p->lodimages[n];
}

void *geometryimage_new(char *s)
{
  ty_geometryimage *p;

  p = (ty_geometryimage *)malloc(sizeof(ty_geometryimage));
  // p->type = C_GEOMETRYIMAGE_TYPE_IMAGE;
  p->nummaxtileimages = 40*40;
  p->tileimages = (void **)malloc(p->nummaxtileimages*sizeof(void *));
  p->numtileimages = 0;
  p->filename = s;
  // p->image = NULL;
  p->xsize = -1;
  p->ysize = -1;
  // p->nummaxlodimages = 10;
  // p->lodimages = (void **)malloc(p->nummaxlodimages*sizeof(void *));
  // p->numlodimages = 0;
  p->xpos = 0.0;
  p->xpos = 0.0;
  // p->zpos = 0.0;
  p->scale = 1.0;

  return (void *)p;
}

char *geometryimage_get_filename(void *pp)
{
  ty_geometryimage *p;

  p = pp;
  return p->filename;
}

void geometryimage_set_size(void *pp, int xsize, int ysize)
{
  ty_geometryimage *p;

  p = pp;
  p->xsize = xsize;
  p->ysize = ysize;
}

int geometryimage_get_xsize(void *pp)
{
  ty_geometryimage *p;

  p = pp;
  return p->xsize;
}

int geometryimage_get_ysize(void *pp)
{
  ty_geometryimage *p;

  p = pp;
  return p->ysize;
}

void geometryimage_set_pos(void *pp, float xpos, float ypos)
{
  ty_geometryimage *p;

  p = pp;
  p->xpos = xpos;
  p->ypos = ypos;
}

float geometryimage_get_xpos(void *pp)
{
  ty_geometryimage *p;

  p = pp;
  return p->xpos;
}

float geometryimage_get_ypos(void *pp)
{
  ty_geometryimage *p;

  p = pp;
  return p->ypos;
}

void geometryimage_set_scale(void *pp, float scale)
{
  ty_geometryimage *p;

  p = pp;
  p->scale = scale;
}

float geometryimage_get_scale(void *pp)
{
  ty_geometryimage *p;

  p = pp;
  return p->scale;
}

#if 0
void geometryimage_set_numlodimages(void *pp, int n)
{
  ty_geometryimage *p;

  p = pp;
  p->numlodimages = n;
}

int geometryimage_get_numlodimages(void *pp)
{
  ty_geometryimage *p;

  p = pp;
  return p->numlodimages;
}

void geometryimage_set_lodimage(void *pp, int n, void *li)
{
  ty_geometryimage *p;

  p = pp;
  p->lodimages[n] = li;
}

void *geometryimage_get_lodimage(void *pp, int n)
{
  ty_geometryimage *p;

  p = pp;
  return p->lodimages[n];
}
#endif

void geometryimage_gi2ig_bound(void *pp, ty_bound *b1, ty_bound *b2)
{
  ty_geometryimage *p;

  p = pp;
  b2->xmin = b1->xmin*p->scale + p->xpos;
  b2->ymin = b1->ymin*p->scale + p->ypos;
  b2->xmax = b1->xmax*p->scale + p->xpos;
  b2->ymax = b1->ymax*p->scale + p->ypos;
}


void geometryimage_add_tileimage(void *pp, void *q)
{
  ty_geometryimage *p;

  p = pp;
  if (p->numtileimages >= p->nummaxtileimages) {
    fprintf(stderr,"Could not add tileimage to gi, max reached\n");
    exit(-1);
  }
  p->tileimages[p->numtileimages] = q;
  p->numtileimages++;
}

int geometryimage_get_numtileimages(void *pp)
{
  ty_geometryimage *p;

  p = pp;
  return p->numtileimages;
}

void *geometryimage_get_tileimage(void *pp, int n)
{
  ty_geometryimage *p;

  p = pp;
  // Check if n is valid.
  return p->tileimages[n];
}

void geometryimage_print(void *pp)
{
  ty_geometryimage *p;
  int i;

  p = pp;
  fprintf(stderr,"%4i %4i %10f %10f %10f\n",p->xsize,p->ysize,p->xpos,p->ypos,p->scale);
}

void *imagegraph_new()
{
  ty_imagegraph *p;
  int i;

  p = (ty_imagegraph *)malloc(sizeof(ty_imagegraph));
  p->maximages = 2000;
  p->images = (void **)malloc(p->maximages*sizeof(void *));
  p->lodimages = (void **)malloc(p->maximages*10*sizeof(void *));
  p->numimages = 0;
  p->xpos = 0.0;
  p->ypos = 0.0;
  p->scale = 1.0;
  p->scale = 0.25; // test

  for (i = 0; i < p->maximages; i++) {
    p->images[i] = NULL;
  }

  for (i = 0; i < 10*p->maximages; i++) {
    p->lodimages[i] = NULL;
  }

  return (void *)p;
}

int imagegraph_get_numimages(void *pp)
{
  ty_imagegraph *p;

  p = pp;
  return p->numimages;
}

void imagegraph_set_pos(void *pp, float xpos, float ypos)
{
  ty_imagegraph *p;

  p = pp;
  p->xpos = xpos;
  p->ypos = ypos;
}

float imagegraph_get_xpos(void *pp)
{
  ty_imagegraph *p;

  p = pp;
  return p->xpos;
}

float imagegraph_get_ypos(void *pp)
{
  ty_imagegraph *p;

  p = pp;
  return p->ypos;
}

void imagegraph_set_scale(void *pp, float scale)
{
  ty_imagegraph *p;

  p = pp;
  p->scale = scale;
}

float imagegraph_get_scale(void *pp)
{
  ty_imagegraph *p;

  p = pp;
  return p->scale;
}

void imagegraph_ig2disp_bound(void *pp, ty_bound *b1, ty_bound *b2)
{
  ty_imagegraph *p;

  p = pp;
  b2->xmin = b1->xmin*p->scale + p->xpos;
  b2->ymin = b1->ymin*p->scale + p->ypos;
  b2->xmax = b1->xmax*p->scale + p->xpos;
  b2->ymax = b1->ymax*p->scale + p->ypos;
}

void imagegraph_print(void *pp)
{
  ty_imagegraph *p;
  int i;

  p = pp;
  fprintf(stderr,"Imagegraph:\n");
  fprintf(stderr,"%f %f %f\n",p->xpos,p->ypos,p->scale);
  for (i = 0; i < p->numimages; i++) {
    fprintf(stderr,"Image %2i: ",i);
    geometryimage_print(p->images[i]);
  }
}



#if 0
// Without a working LOD.

void imagegraph_render(void *pp, void *displayimage, float scale, float xcenter, float ycenter)
{
  ty_imagegraph *p;
  ty_geometryimage *q;
  int i,j;
  int axmin,aymin,axmax,aymax;
  int lod;

  p = pp;
  image_clean(displayimage);
  for (i = 0; i < p->numimages; i++) {
#if 1
    q = p->images[i];
    if (q->image == NULL) {
      q->image = openimage(q->filename);
    }
#endif
#if 0
    // LOD selection.
    lod = (int)(log(scale)/log(2.0));
    fprintf(stderr,"lod = %i\n",lod);
    if (lod < 0) lod = 0;
    if (lod > 4) lod = 4; // See createlods() for this value.
    q = p->lodimages[10*i + lod];
    if (q->image == NULL) {
      for (j = 0; j <= 4; j++) {
	if (((ty_geometryimage *)(p->lodimages[10*i + j]))->image != NULL) {
	  image_free(((ty_geometryimage *)(p->lodimages[10*i + j]))->image);
	  ((ty_geometryimage *)(p->lodimages[10*i + j]))->image = NULL;
	}
      }
      q->image = openimage(q->filename);
    }
#endif
    if (q->image == NULL) {
      fprintf(stderr,"could not open image %s\n",q->filename);
    } else {
      // image_scale_zoom_add(q->image,displayimage,q->scale*scale,q->xpos+xcenter,q->ypos+ycenter);
      axmin = (0.0 - (q->xpos+xcenter))/(q->scale*scale) + (float)image_get_xsize(displayimage)/2.0;
      aymin = (0.0 - (q->ypos+ycenter))/(q->scale*scale) + (float)image_get_ysize(displayimage)/2.0;
      axmax = ((float)image_get_xsize(q->image) - (q->xpos+xcenter))/(q->scale*scale) + (float)image_get_xsize(displayimage)/2.0;
      aymax = ((float)image_get_ysize(q->image) - (q->ypos+ycenter))/(q->scale*scale) + (float)image_get_ysize(displayimage)/2.0;
      if (axmin < 0) axmin = 0;
      if (aymin < 0) aymin = 0;
      if (axmax > image_get_xsize(displayimage) - 1) axmax = image_get_xsize(displayimage) - 1;
      if (aymax > image_get_ysize(displayimage) - 1) aymax = image_get_ysize(displayimage) - 1;
      // image_scale_zoom_add_area(q->image,displayimage,q->scale*scale,q->xpos+xcenter,q->ypos+ycenter,axmin,aymin,axmax,aymax);
      image_scale_zoom_max_area(q->image,displayimage,q->scale*scale,q->xpos+xcenter,q->ypos+ycenter,axmin,aymin,axmax,aymax);
    }
  }
}

void imagegraph_render_area(void *pp, void *displayimage, float scale, float xcenter, float ycenter, int xmin, int ymin, int xmax, int ymax)
{
  ty_imagegraph *p;
  ty_geometryimage *q;
  int i,j;
  int axmin,aymin,axmax,aymax;
  int bxmin,bymin,bxmax,bymax;
  int lod;

  p = pp;
  image_clean(displayimage);
  for (i = 0; i < p->numimages; i++) {
#if 1
    q = p->images[i];
    if (q->image == NULL) {
      q->image = openimage(q->filename);
    }
#endif
#if 0
    // LOD selection.
    lod = (int)(log(scale)/log(2.0));
    fprintf(stderr,"lod = %i\n",lod);
    if (lod < 0) lod = 0;
    if (lod > 4) lod = 4; // See createlods() for this value.
    q = p->lodimages[10*i + lod];
    if (q->image == NULL) {
      for (j = 0; j <= 4; j++) {
	if (((ty_geometryimage *)(p->lodimages[10*i + j]))->image != NULL) {
	  image_free(((ty_geometryimage *)(p->lodimages[10*i + j]))->image);
	  ((ty_geometryimage *)(p->lodimages[10*i + j]))->image = NULL;
	}
      }
      q->image = openimage(q->filename);
    }
#endif
    if (q->image == NULL) {
      fprintf(stderr,"could not open image %s\n",q->filename);
    } else {
      // image_scale_zoom_add_area(q->image,displayimage,q->scale*scale,q->xpos+xcenter,q->ypos+ycenter,xmin,ymin,xmax,ymax);
      axmin = (0.0 - (q->xpos+xcenter))/(q->scale*scale) + (float)image_get_xsize(displayimage)/2.0;
      aymin = (0.0 - (q->ypos+ycenter))/(q->scale*scale) + (float)image_get_ysize(displayimage)/2.0;
      axmax = ((float)image_get_xsize(q->image) - (q->xpos+xcenter))/(q->scale*scale) + (float)image_get_xsize(displayimage)/2.0;
      aymax = ((float)image_get_ysize(q->image) - (q->ypos+ycenter))/(q->scale*scale) + (float)image_get_ysize(displayimage)/2.0;
      if (axmin < 0) axmin = 0;
      if (aymin < 0) aymin = 0;
      if (axmax > image_get_xsize(displayimage) - 1) axmax = image_get_xsize(displayimage) - 1;
      if (aymax > image_get_ysize(displayimage) - 1) aymax = image_get_ysize(displayimage) - 1;

      // Intersection of the areas.

      if (xmin < axmin) bxmin = axmin;
      else bxmin = xmin;
      if (ymin < aymin) bymin = aymin;
      else bymin = ymin;
      if (xmax < axmax) bxmax = xmax;
      else bxmax = axmax;
      if (ymax < aymax) bymax = ymax;
      else bymax = aymax;

      // image_scale_zoom_add_area(q->image,displayimage,q->scale*scale,q->xpos+xcenter,q->ypos+ycenter,bxmin,bymin,bxmax,bymax);
      image_scale_zoom_max_area(q->image,displayimage,q->scale*scale,q->xpos+xcenter,q->ypos+ycenter,bxmin,bymin,bxmax,bymax);
    }
  }
}

#endif

// LOD with ty_lodimage.

#if 0
// The whole display is also rendered with imagegraph_render_area().

void imagegraph_render(void *pp, void *displayimage, float scale, float xcenter, float ycenter)
{
  ty_imagegraph *ig;
  ty_geometryimage *gi;
  int i,j;
  int axmin,aymin,axmax,aymax;
  int lod;
  void *image;
  int pixels;
  void *li;
  int done;
  int donelod;
  float liscale;

  ig = pp;
  image_clean(displayimage);
  for (i = 0; i < ig->numimages; i++) {
    gi = ig->images[i];
    // LOD selection.
    // Put the lodimages to screen starting from the
    // smallest. Stop to the first lodimage which has
    // more pixels than on the screen.
    // Compare to gi->xsize,gi->ysize which tells the
    // true image size.

    // Project the original image to screen.
    axmin = (0.0 - (gi->xpos+xcenter))/(gi->scale*scale) + (float)image_get_xsize(displayimage)/2.0;
    aymin = (0.0 - (gi->ypos+ycenter))/(gi->scale*scale) + (float)image_get_ysize(displayimage)/2.0;
    axmax = ((float)gi->xsize - (gi->xpos+xcenter))/(gi->scale*scale) + (float)image_get_xsize(displayimage)/2.0;
    aymax = ((float)gi->ysize - (gi->ypos+ycenter))/(gi->scale*scale) + (float)image_get_ysize(displayimage)/2.0;
    // Must not to clip to display.
    // How many pixels are covered?
    pixels = axmax-axmin+1;

    // Then check the lodimages.
    done = 0;
    donelod = 0;
    for (lod = gi->numlodimages-1; (lod >= 0) && (done == 0); lod--) {
      li = geometryimage_get_lodimage(gi,lod);
      fprintf(stderr,"lod = %i, xsize = %i, pixels = %i\n",lod,lodimage_get_xsize(li),pixels);
      if (lodimage_get_xsize(li) >= pixels) {
	done = 1;
	donelod = lod;
      }
    }
    lod = donelod;
    fprintf(stderr,"lod = %i\n",lod);
    if (lod < 0) lod = 0;
    li = geometryimage_get_lodimage(gi,lod);

    if (lodimage_get_image(li) == NULL) {
      // Free the previous LOD.
      for (j = 0; j < geometryimage_get_numlodimages(gi); j++) {
	if (lodimage_get_image(geometryimage_get_lodimage(gi,j)) != NULL) {
	  image_free(lodimage_get_image(geometryimage_get_lodimage(gi,j)));
	  lodimage_set_image(geometryimage_get_lodimage(gi,j),NULL);
	}
      }
      lodimage_set_image(li,openimage(lodimage_get_filename(li)));
      fprintf(stderr,"opened image %s\n",lodimage_get_filename(li));
    }

    image = lodimage_get_image(li);
    liscale = lodimage_get_scale(li);
    if (image == NULL) {
      fprintf(stderr,"could not open image %s\n",lodimage_get_filename(li));
    } else {
      axmin = (0.0 - (gi->xpos+xcenter))/(gi->scale*scale) + (float)image_get_xsize(displayimage)/2.0;
      aymin = (0.0 - (gi->ypos+ycenter))/(gi->scale*scale) + (float)image_get_ysize(displayimage)/2.0;
      axmax = ((float)image_get_xsize(image)*liscale - (gi->xpos+xcenter))/(gi->scale*scale) + (float)image_get_xsize(displayimage)/2.0;
      aymax = ((float)image_get_ysize(image)*liscale - (gi->ypos+ycenter))/(gi->scale*scale) + (float)image_get_ysize(displayimage)/2.0;
      if (axmin < 0) axmin = 0;
      if (aymin < 0) aymin = 0;
      if (axmax > image_get_xsize(displayimage) - 1) axmax = image_get_xsize(displayimage) - 1;
      if (aymax > image_get_ysize(displayimage) - 1) aymax = image_get_ysize(displayimage) - 1;
      // image_scale_zoom_add_area(image,displayimage,gi->scale*scale,gi->xpos+xcenter,gi->ypos+ycenter,axmin,aymin,axmax,aymax);
      image_scale_zoom_max_area(image,displayimage,gi->scale*scale/liscale,gi->xpos+xcenter,gi->ypos+ycenter,axmin,aymin,axmax,aymax);
    }
  }
}
#endif

#if 0
// Before moving to (0,0) based.
void imagegraph_render_area(void *pp, void *displayimage, float igscale, float igxpos, float igypos, int xmin, int ymin, int xmax, int ymax)
{
  ty_imagegraph *ig;
  ty_geometryimage *gi;
  int i,j;
  int axmin,aymin,axmax,aymax;
  int bxmin,bymin,bxmax,bymax;
  int lod;
  void *image;
  int pixels;
  void *li;
  int done;
  int donelod;
  float liscale;

  ig = pp;
  image_clean(displayimage);
  for (i = 0; i < ig->numimages; i++) {
    gi = ig->images[i];
    // LOD selection.
    // Put the lodimages to screen starting from the
    // smallest. Stop to the first lodimage which has
    // more pixels than on the screen.
    // Compare to gi->xsize,gi->ysize which tells the
    // true image size.

    // Project the original image to screen.
    axmin = (0.0 - (gi->xpos+xcenter))/(gi->scale*scale) + (float)image_get_xsize(displayimage)/2.0;
    aymin = (0.0 - (gi->ypos+ycenter))/(gi->scale*scale) + (float)image_get_ysize(displayimage)/2.0;
    axmax = ((float)gi->xsize - (gi->xpos+xcenter))/(gi->scale*scale) + (float)image_get_xsize(displayimage)/2.0;
    aymax = ((float)gi->ysize - (gi->ypos+ycenter))/(gi->scale*scale) + (float)image_get_ysize(displayimage)/2.0;
    // Must not to clip to display.
    // How many pixels are covered?
    pixels = axmax-axmin+1;

    // Then check the lodimages.
    done = 0;
    donelod = 0;
    for (lod = gi->numlodimages-1; (lod >= 0) && (done == 0); lod--) {
      li = geometryimage_get_lodimage(gi,lod);
      fprintf(stderr,"lod = %i, xsize = %i, pixels = %i\n",lod,lodimage_get_xsize(li),pixels);
      if (lodimage_get_xsize(li) >= pixels) {
	done = 1;
	donelod = lod;
      }
    }
    lod = donelod;
    fprintf(stderr,"lod = %i\n",lod);
    if (lod < 0) lod = 0;
    li = geometryimage_get_lodimage(gi,lod);
    
    if (lodimage_get_image(li) == NULL) {
      // Free the previous LOD.
      for (j = 0; j < geometryimage_get_numlodimages(gi); j++) {
	if (lodimage_get_image(geometryimage_get_lodimage(gi,j)) != NULL) {
	  image_free(lodimage_get_image(geometryimage_get_lodimage(gi,j)));
	  lodimage_set_image(geometryimage_get_lodimage(gi,j),NULL);
	}
      }
      lodimage_set_image(li,openimage(lodimage_get_filename(li)));
      fprintf(stderr,"opened image %s\n",lodimage_get_filename(li));
    }

    image = lodimage_get_image(li);
    liscale = lodimage_get_scale(li);
    if (image == NULL) {
      fprintf(stderr,"could not open image %s\n",lodimage_get_filename(li));
    } else {
      axmin = (0.0 - (gi->xpos+xcenter))/(gi->scale*scale) + (float)image_get_xsize(displayimage)/2.0;
      aymin = (0.0 - (gi->ypos+ycenter))/(gi->scale*scale) + (float)image_get_ysize(displayimage)/2.0;
      axmax = ((float)image_get_xsize(image)*liscale - (gi->xpos+xcenter))/(gi->scale*scale) + (float)image_get_xsize(displayimage)/2.0;
      aymax = ((float)image_get_ysize(image)*liscale - (gi->ypos+ycenter))/(gi->scale*scale) + (float)image_get_ysize(displayimage)/2.0;
      if (axmin < 0) axmin = 0;
      if (aymin < 0) aymin = 0;
      if (axmax > image_get_xsize(displayimage) - 1) axmax = image_get_xsize(displayimage) - 1;
      if (aymax > image_get_ysize(displayimage) - 1) aymax = image_get_ysize(displayimage) - 1;

      // Intersection of the areas.

      if (xmin < axmin) bxmin = axmin;
      else bxmin = xmin;
      if (ymin < aymin) bymin = aymin;
      else bymin = ymin;
      if (xmax < axmax) bxmax = xmax;
      else bxmax = axmax;
      if (ymax < aymax) bymax = ymax;
      else bymax = aymax;

      // image_scale_zoom_add_area(image,displayimage,gi->scale*scale,gi->xpos+xcenter,gi->ypos+ycenter,axmin,aymin,axmax,aymax);
      // image_scale_zoom_max_area(image,displayimage,gi->scale*scale,gi->xpos+xcenter,gi->ypos+ycenter,axmin,aymin,axmax,aymax);
      image_scale_zoom_max_area(image,displayimage,gi->scale*scale/liscale,gi->xpos+xcenter,gi->ypos+ycenter,bxmin,bymin,bxmax,bymax);
    }
  }
}
#endif

#if 0
// Used before tiles and gi as container.
// (0,0) based.
void imagegraph_render_area(void *pp, void *displayimage, float igscale, float igxpos, float igypos, int xmin, int ymin, int xmax, int ymax)
{
  ty_imagegraph *ig;
  ty_geometryimage *gi;
  int i,j;
  int axmin,aymin,axmax,aymax;
  int bxmin,bymin,bxmax,bymax;
  int lod;
  void *image;
  int pixels;
  void *li;
  int done;
  int donelod;
  float liscale;
  ty_bound b1;
  ty_bound b2;

  ig = pp;
  image_clean(displayimage);
  for (i = 0; i < ig->numimages; i++) {
    gi = ig->images[i];
    // LOD selection.
    // Put the lodimages to screen starting from the
    // smallest. Stop to the first lodimage which has
    // more pixels than on the screen.
    // Compare to gi->xsize,gi->ysize which tells the
    // true image size.

    // Project the original image to screen.
    b1.xmin = 0.0;
    b1.ymin = 0.0;
    b1.xmax = (float)gi->xsize;
    b1.ymax = (float)gi->ysize;
    geometryimage_gi2ig_bound(gi,&b1,&b2);
    imagegraph_ig2disp_bound(ig,&b2,&b1);

    // The render area stays fixed for all LOD images.
    axmin = b1.xmin;
    aymin = b1.ymin;
    axmax = b1.xmax;
    aymax = b1.ymax;
    if (axmin < 0) axmin = 0;
    if (aymin < 0) aymin = 0;
    if (axmax > image_get_xsize(displayimage) - 1) axmax = image_get_xsize(displayimage) - 1;
    if (aymax > image_get_ysize(displayimage) - 1) aymax = image_get_ysize(displayimage) - 1;

    // XXXX Extend this area outside the display.
    // XXXX Can be done above.
    if ((axmax - axmin >= 0) && (aymax - aymin >= 0)) {
      // Visible in display or near display.
    } else {
      // Not visible, or not near the display.
      // Free the previous LOD.
      for (j = 0; j < geometryimage_get_numlodimages(gi); j++) {
	if (lodimage_get_image(geometryimage_get_lodimage(gi,j)) != NULL) {
	  image_free(lodimage_get_image(geometryimage_get_lodimage(gi,j)));
	  lodimage_set_image(geometryimage_get_lodimage(gi,j),NULL);
	}
      }
    }

    // Intersection of the areas.

    if (xmin < axmin) bxmin = axmin;
    else bxmin = xmin;
    if (ymin < aymin) bymin = aymin;
    else bymin = ymin;
    if (xmax < axmax) bxmax = xmax;
    else bxmax = axmax;
    if (ymax < aymax) bymax = ymax;
    else bymax = aymax;

#if 1
    // XXXX Now back.
    // XXXX Moved below.
    // Render only if visible.
    // XXXX Latest LOD of non-visible images is not deleted.
    // For zooming-in that might be good, but for panning
    // that is bad because images stay in memory.
    if ((bxmax - bxmin >= 0) && (bymax - bymin >= 0)) {
#endif

      // Do not use the clipped version in axmin etc.
      // How many pixels are covered?
      pixels = b1.xmax - b1.xmin + 1;

      // Then check the lodimages.
      done = 0;
      donelod = 0;
      for (lod = gi->numlodimages-1; (lod >= 0) && (done == 0); lod--) {
	li = geometryimage_get_lodimage(gi,lod);
	// fprintf(stderr,"lod = %i, xsize = %i, pixels = %i\n",lod,lodimage_get_xsize(li),pixels);
	if (lodimage_get_xsize(li) >= pixels) {
	  done = 1;
	  donelod = lod;
	}
      }
      // donelod = 0; // test
      lod = donelod;
      // fprintf(stderr,"test lod = %i\n",lod);
      // fprintf(stderr,"lod = %i\n",lod);
      if (lod < 0) lod = 0;
      li = geometryimage_get_lodimage(gi,lod);

      if (lodimage_get_image(li) == NULL) {
	// Free the previous LOD.
	for (j = 0; j < geometryimage_get_numlodimages(gi); j++) {
	  if (lodimage_get_image(geometryimage_get_lodimage(gi,j)) != NULL) {
	    image_free(lodimage_get_image(geometryimage_get_lodimage(gi,j)));
	    lodimage_set_image(geometryimage_get_lodimage(gi,j),NULL);
	  }
	}
	lodimage_set_image(li,openimage(lodimage_get_filename(li)));
	fprintf(stderr,"opened image %s\n",lodimage_get_filename(li));
      }


#if 0
      // XXXX When image goes out of display, it is not deleted.

      // XXXX Use of bxmin etc is wrong, we need to test
      // XXXX b1 bound against the entire display.
      // XXXX bxmin is only within the updated area which can
      // XXXX be small when the imagegraph is moved.

      // Render only if visible.
      if ((bxmax - bxmin >= 0) && (bymax - bymin >= 0)) {

	if (lodimage_get_image(li) == NULL) {
	  lodimage_set_image(li,openimage(lodimage_get_filename(li)));
	  fprintf(stderr,"opened image %s\n",lodimage_get_filename(li));
	}
#endif

	image = lodimage_get_image(li);
	liscale = lodimage_get_scale(li);
	if (image == NULL) {
	  fprintf(stderr,"could not open image %s\n",lodimage_get_filename(li));
	} else {

	  // image_scale_zoom_add_area(image,displayimage,gi->scale*scale,gi->xpos+xcenter,gi->ypos+ycenter,axmin,aymin,axmax,aymax);
	  // image_scale_zoom_max_area(image,displayimage,gi->scale*scale,gi->xpos+xcenter,gi->ypos+ycenter,axmin,aymin,axmax,aymax);
	  image_scale_zoom_max_area(image,displayimage,gi->scale*ig->scale*liscale,gi->xpos*ig->scale + ig->xpos,gi->ypos*ig->scale + ig->ypos,bxmin,bymin,bxmax,bymax);
	}

#if 0
      }
#endif
    }
  }
}
#endif



void tileimage_render(void *pp, void *oo, void *qq, void *displayimage, int xmin, int ymin, int xmax, int ymax)
{
  ty_imagegraph *ig;
  ty_geometryimage *gi;
  ty_tileimage *ti;
  int i,j;
  int axmin,aymin,axmax,aymax;
  int bxmin,bymin,bxmax,bymax;
  int lod;
  void *image;
  int pixels;
  void *li;
  int done;
  int donelod;
  float liscale;
  ty_bound b1;
  ty_bound b2;

  ti = pp;
  gi = oo;
  ig = qq;

  // LOD selection.
  // Put the lodimages to screen starting from the
  // smallest. Stop to the first lodimage which has
  // more pixels than on the screen.
  // Compare to gi->xsize,gi->ysize which tells the
  // true image size.

  // Project the original image to screen.
  b1.xmin = ti->xpos;
  b1.ymin = ti->ypos;
  b1.xmax = ti->xpos + (float)ti->xsize;
  b1.ymax = ti->ypos + (float)ti->ysize;
  geometryimage_gi2ig_bound(gi,&b1,&b2);
  imagegraph_ig2disp_bound(ig,&b2,&b1);

  // The render area stays fixed for all LOD images.
  axmin = b1.xmin;
  aymin = b1.ymin;
  axmax = b1.xmax;
  aymax = b1.ymax;
  if (axmin < 0) axmin = 0;
  if (aymin < 0) aymin = 0;
  if (axmax > image_get_xsize(displayimage) - 1) axmax = image_get_xsize(displayimage) - 1;
  if (aymax > image_get_ysize(displayimage) - 1) aymax = image_get_ysize(displayimage) - 1;

  // XXXX Extend this area outside the display.
  // XXXX Can be done above.
  if ((axmax - axmin >= 0) && (aymax - aymin >= 0)) {
    // Visible in display or near display.
  } else {
    // Not visible, or not near the display.
    // Free the previous LOD.
    for (j = 0; j < tileimage_get_numlodimages(ti); j++) {
      if (lodimage_get_image(tileimage_get_lodimage(ti,j)) != NULL) {
	image_free(lodimage_get_image(tileimage_get_lodimage(ti,j)));
	lodimage_set_image(tileimage_get_lodimage(ti,j),NULL);
      }
    }
  }

  // Intersection of the areas.

  if (xmin < axmin) bxmin = axmin;
  else bxmin = xmin;
  if (ymin < aymin) bymin = aymin;
  else bymin = ymin;
  if (xmax < axmax) bxmax = xmax;
  else bxmax = axmax;
  if (ymax < aymax) bymax = ymax;
  else bymax = aymax;

  // Render only if visible.
  // XXXX Latest LOD of non-visible images is not deleted.
  // For zooming-in that might be good, but for panning
  // that is bad because images stay in memory.
  if ((bxmax - bxmin >= 0) && (bymax - bymin >= 0)) {

    // Do not use the clipped version in axmin etc.
    // How many pixels are covered?
    pixels = b1.xmax - b1.xmin + 1;

    // Then check the lodimages.
    done = 0;
    donelod = 0;
    for (lod = ti->numlodimages-1; (lod >= 0) && (done == 0); lod--) {
      li = tileimage_get_lodimage(ti,lod);
      // fprintf(stderr,"lod = %i, xsize = %i, pixels = %i\n",lod,lodimage_get_xsize(li),pixels);
      if (lodimage_get_xsize(li) >= pixels) {
	done = 1;
	donelod = lod;
      }
    }
    // donelod = 0; // test
    lod = donelod;
    // fprintf(stderr,"test lod = %i\n",lod);
    // fprintf(stderr,"lod = %i\n",lod);
    if (lod < 0) lod = 0;
    li = tileimage_get_lodimage(ti,lod);

    if (lodimage_get_image(li) == NULL) {
      // Free the previous LOD.
      for (j = 0; j < tileimage_get_numlodimages(ti); j++) {
	if (lodimage_get_image(tileimage_get_lodimage(ti,j)) != NULL) {
	  image_free(lodimage_get_image(tileimage_get_lodimage(ti,j)));
	  lodimage_set_image(tileimage_get_lodimage(ti,j),NULL);
	}
      }
      lodimage_set_image(li,openimage(lodimage_get_filename(li)));
      // fprintf(stderr,"opened image %s\n",lodimage_get_filename(li));
    }

    image = lodimage_get_image(li);
    liscale = lodimage_get_scale(li);
    if (image == NULL) {
      fprintf(stderr,"could not open image %s\n",lodimage_get_filename(li));
    } else {

      // image_scale_zoom_add_area(image,displayimage,gi->scale*scale,gi->xpos+xcenter,gi->ypos+ycenter,axmin,aymin,axmax,aymax);
      // image_scale_zoom_max_area(image,displayimage,gi->scale*scale,gi->xpos+xcenter,gi->ypos+ycenter,axmin,aymin,axmax,aymax);
      image_scale_zoom_max_area(image,displayimage,gi->scale*ig->scale*liscale,(ti->xpos*gi->scale + gi->xpos)*ig->scale + ig->xpos,(ti->ypos*gi->scale + gi->ypos)*ig->scale + ig->ypos,bxmin,bymin,bxmax,bymax);
      // fprintf(stderr,"rendered tile lod %s\n",lodimage_get_filename(li));
    }

  }

}


void geometryimage_render(void *pp, void *ig, void *displayimage, int xmin, int ymin, int xmax, int ymax)
{
  ty_geometryimage *gi;
  int i;

  gi = pp;

  for (i = 0; i < gi->numtileimages; i++) {
    tileimage_render(gi->tileimages[i],gi,ig,displayimage,xmin,ymin,xmax,ymax);
  }
}


// Tiles and gi as container.
// (0,0) based.
void imagegraph_render_area(void *pp, void *displayimage, float igscale, float igxpos, float igypos, int xmin, int ymin, int xmax, int ymax)
{
  ty_imagegraph *ig;
  ty_geometryimage *gi;
  int i;

  ig = pp;
  image_clean(displayimage);
  for (i = 0; i < ig->numimages; i++) {
    gi = ig->images[i];

    geometryimage_render(gi,ig,displayimage,xmin,ymin,xmax,ymax);

  }
}


#if 0
// Old. When used?
void imagegraph_render_area(void *pp, void *displayimage, float igscale, float igxpos, float igypos, int xmin, int ymin, int xmax, int ymax)
{
  ty_imagegraph *ig;
  ty_geometryimage *gi;
  int i,j;
  int axmin,aymin,axmax,aymax;
  int bxmin,bymin,bxmax,bymax;
  int lod;
  void *image;
  int pixels;
  void *li;
  int done;
  int donelod;
  float liscale;

  ig = pp;
  image_clean(displayimage);
  for (i = 0; i < ig->numimages; i++) {
    gi = ig->images[i];
    // LOD selection.
    // Put the lodimages to screen starting from the
    // smallest. Stop to the first lodimage which has
    // more pixels than on the screen.
    // Compare to gi->xsize,gi->ysize which tells the
    // true image size.

    // Project the original image to screen.
    axmin = (0.0 - (gi->xpos+xcenter))/(gi->scale*scale) + (float)image_get_xsize(displayimage)/2.0;
    aymin = (0.0 - (gi->ypos+ycenter))/(gi->scale*scale) + (float)image_get_ysize(displayimage)/2.0;
    axmax = ((float)gi->xsize - (gi->xpos+xcenter))/(gi->scale*scale) + (float)image_get_xsize(displayimage)/2.0;
    aymax = ((float)gi->ysize - (gi->ypos+ycenter))/(gi->scale*scale) + (float)image_get_ysize(displayimage)/2.0;
    // Must not to clip to display.
    // How many pixels are covered?
    pixels = axmax-axmin+1;

    // Then check the lodimages.
    done = 0;
    donelod = 0;
    for (lod = gi->numlodimages-1; (lod >= 0) && (done == 0); lod--) {
      li = geometryimage_get_lodimage(gi,lod);
      fprintf(stderr,"lod = %i, xsize = %i, pixels = %i\n",lod,lodimage_get_xsize(li),pixels);
      if (lodimage_get_xsize(li) >= pixels) {
	done = 1;
	donelod = lod;
      }
    }
    lod = donelod;
    fprintf(stderr,"lod = %i\n",lod);
    if (lod < 0) lod = 0;
    li = geometryimage_get_lodimage(gi,lod);
    
    if (lodimage_get_image(li) == NULL) {
      // Free the previous LOD.
      for (j = 0; j < geometryimage_get_numlodimages(gi); j++) {
	if (lodimage_get_image(geometryimage_get_lodimage(gi,j)) != NULL) {
	  image_free(lodimage_get_image(geometryimage_get_lodimage(gi,j)));
	  lodimage_set_image(geometryimage_get_lodimage(gi,j),NULL);
	}
      }
      lodimage_set_image(li,openimage(lodimage_get_filename(li)));
      fprintf(stderr,"opened image %s\n",lodimage_get_filename(li));
    }

    image = lodimage_get_image(li);
    liscale = lodimage_get_scale(li);
    if (image == NULL) {
      fprintf(stderr,"could not open image %s\n",lodimage_get_filename(li));
    } else {
      axmin = (0.0 - (gi->xpos+xcenter))/(gi->scale*scale) + (float)image_get_xsize(displayimage)/2.0;
      aymin = (0.0 - (gi->ypos+ycenter))/(gi->scale*scale) + (float)image_get_ysize(displayimage)/2.0;
      axmax = ((float)image_get_xsize(image)*liscale - (gi->xpos+xcenter))/(gi->scale*scale) + (float)image_get_xsize(displayimage)/2.0;
      aymax = ((float)image_get_ysize(image)*liscale - (gi->ypos+ycenter))/(gi->scale*scale) + (float)image_get_ysize(displayimage)/2.0;
      if (axmin < 0) axmin = 0;
      if (aymin < 0) aymin = 0;
      if (axmax > image_get_xsize(displayimage) - 1) axmax = image_get_xsize(displayimage) - 1;
      if (aymax > image_get_ysize(displayimage) - 1) aymax = image_get_ysize(displayimage) - 1;

      // Intersection of the areas.

      if (xmin < axmin) bxmin = axmin;
      else bxmin = xmin;
      if (ymin < aymin) bymin = aymin;
      else bymin = ymin;
      if (xmax < axmax) bxmax = xmax;
      else bxmax = axmax;
      if (ymax < aymax) bymax = ymax;
      else bymax = aymax;

      // image_scale_zoom_add_area(image,displayimage,gi->scale*scale,gi->xpos+xcenter,gi->ypos+ycenter,axmin,aymin,axmax,aymax);
      // image_scale_zoom_max_area(image,displayimage,gi->scale*scale,gi->xpos+xcenter,gi->ypos+ycenter,axmin,aymin,axmax,aymax);
      image_scale_zoom_max_area(image,displayimage,gi->scale*scale/liscale,gi->xpos+xcenter,gi->ypos+ycenter,bxmin,bymin,bxmax,bymax);
    }
  }
}
#endif


#if 0
// Old. When used?
void imagegraph_render_area(void *pp, void *displayimage, float scale, float xcenter, float ycenter, int xmin, int ymin, int xmax, int ymax)
{
  ty_imagegraph *p;
  ty_geometryimage *q;
  int i,j;
  int axmin,aymin,axmax,aymax;
  int bxmin,bymin,bxmax,bymax;
  int lod;

  p = pp;
  image_clean(displayimage);
  for (i = 0; i < p->numimages; i++) {
#if 1
    q = p->images[i];
    if (q->image == NULL) {
      q->image = openimage(q->filename);
    }
#endif
#if 0
    // LOD selection.
    lod = (int)(log(scale)/log(2.0));
    fprintf(stderr,"lod = %i\n",lod);
    if (lod < 0) lod = 0;
    if (lod > 4) lod = 4; // See createlods() for this value.
    q = p->lodimages[10*i + lod];
    if (q->image == NULL) {
      for (j = 0; j <= 4; j++) {
	if (((ty_geometryimage *)(p->lodimages[10*i + j]))->image != NULL) {
	  image_free(((ty_geometryimage *)(p->lodimages[10*i + j]))->image);
	  ((ty_geometryimage *)(p->lodimages[10*i + j]))->image = NULL;
	}
      }
      q->image = openimage(q->filename);
    }
#endif
    if (q->image == NULL) {
      fprintf(stderr,"could not open image %s\n",q->filename);
    } else {
      // image_scale_zoom_add_area(q->image,displayimage,q->scale*scale,q->xpos+xcenter,q->ypos+ycenter,xmin,ymin,xmax,ymax);
      axmin = (0.0 - (q->xpos+xcenter))/(q->scale*scale) + (float)image_get_xsize(displayimage)/2.0;
      aymin = (0.0 - (q->ypos+ycenter))/(q->scale*scale) + (float)image_get_ysize(displayimage)/2.0;
      axmax = ((float)image_get_xsize(q->image) - (q->xpos+xcenter))/(q->scale*scale) + (float)image_get_xsize(displayimage)/2.0;
      aymax = ((float)image_get_ysize(q->image) - (q->ypos+ycenter))/(q->scale*scale) + (float)image_get_ysize(displayimage)/2.0;
      if (axmin < 0) axmin = 0;
      if (aymin < 0) aymin = 0;
      if (axmax > image_get_xsize(displayimage) - 1) axmax = image_get_xsize(displayimage) - 1;
      if (aymax > image_get_ysize(displayimage) - 1) aymax = image_get_ysize(displayimage) - 1;

      // Intersection of the areas.

      if (xmin < axmin) bxmin = axmin;
      else bxmin = xmin;
      if (ymin < aymin) bymin = aymin;
      else bymin = ymin;
      if (xmax < axmax) bxmax = xmax;
      else bxmax = axmax;
      if (ymax < aymax) bymax = ymax;
      else bymax = aymax;

      // image_scale_zoom_add_area(q->image,displayimage,q->scale*scale,q->xpos+xcenter,q->ypos+ycenter,bxmin,bymin,bxmax,bymax);
      image_scale_zoom_max_area(q->image,displayimage,q->scale*scale,q->xpos+xcenter,q->ypos+ycenter,bxmin,bymin,bxmax,bymax);
    }
  }
}
#endif


void addimagestoimagegraph(void *pp)
{
  ty_viewer *p;
  ty_imagegraph *q;
  int i;
  int r;
  float rx;
  float ry;

  p = pp;
  q = p->imagegraph;

  q->images = (void **)malloc(p->numfiles*sizeof(void *));
  q->numimages = 0;

  for (i = 0; i < p->numfiles; i++) {
    r = checkimage(p->filenames[i]);
    if (r != 0) {
      // There is no links between p->filenames and q->images
      // other than the name.
      q->images[q->numimages] = geometryimage_new(p->filenames[i]);
      // rx = (float)p->topwindow_xsize*random_float(p->random);
      // ry = (float)p->topwindow_ysize*random_float(p->random);
#if 0
      rx = 3200.0*random_float(p->random);
      ry = 3200.0*random_float(p->random);
#endif
      geometryimage_set_pos(q->images[q->numimages],rx,ry);
      geometryimage_set_scale(q->images[q->numimages],0.2);
      q->numimages++;
    }
  }
}

char tmp_s[2000];

// Case 1:
// First tile the original. Then create LODs for each tile.
void create_tiles_and_lods(void *pp)
{
  ty_viewer *p;
  ty_imagegraph *ig;
  ty_geometryimage *gi;
  ty_tileimage *ti;
  int i;
  int r;
  float rx;
  float ry;
  void *origimage;
  void *tileimage;
  void *lodimage;
  void *li;
  int loddiv;
  int lodlevel;
  int x,y;
  int tilexsize,tileysize;
  int lodxsize,lodysize;
  int hastilefile,haslodfile;

  p = pp;
  ig = p->imagegraph;

  for (i = 0; i < ig->numimages; i++) {
    gi = ig->images[i];
    origimage = openimage(gi->filename);
    if (origimage != NULL) {
      geometryimage_set_size(gi,image_get_xsize(origimage),image_get_ysize(origimage));
      // geometryimage_set_type(gi,C_GEOMETRYIMAGE_TYPE_CONTAINER);

      for (y = 0; y < image_get_ysize(origimage); y += C_TILE_YSIZE) {
	if (image_get_ysize(origimage) - y < C_TILE_YSIZE) {
	  tileysize = image_get_ysize(origimage) - y;
	} else {
	  tileysize = C_TILE_YSIZE;
	}
	for (x = 0; x < image_get_xsize(origimage); x += C_TILE_XSIZE) {
	  if (image_get_xsize(origimage) - x < C_TILE_XSIZE) {
	    tilexsize = image_get_xsize(origimage) - x;
	  } else {
	    tilexsize = C_TILE_XSIZE;
	  }

	  // <image number>_<tile x>_<tile y>_<lod level>.ppm
	  sprintf(tmp_s,"/home/juhana/lodimages/%i",i);
	  mkdir(tmp_s,0755);
	  sprintf(tmp_s,"/home/juhana/lodimages/%i/%i_%i_%i_0.ppm",i,i,x,y);
	  hastilefile = file_exists_name(tmp_s);
	  if (hastilefile == 0) {
	    tileimage = image_new_rgb(tilexsize,tileysize);
	    image_copy_rectangle(origimage,x,y,x+tilexsize-1,y+tileysize-1,tileimage,0,0);
	    image_save_file(tileimage,tmp_s);
	  }
	  ti = tileimage_new(strdup(tmp_s));
	  tileimage_set_size(ti,tilexsize,tileysize);
	  tileimage_set_pos(ti,x,y);

	  li = lodimage_new(tileimage_get_filename(ti));
	  lodimage_set_size(li,tilexsize,tileysize);
	  tileimage_set_lodimage(ti,0,li);

	  loddiv = 1;
	  for (lodlevel = 1; lodlevel <= 4; lodlevel++) {
	    loddiv *= 2;
	    lodxsize = tilexsize/loddiv;
	    lodysize = tileysize/loddiv;
	    sprintf(tmp_s,"/home/juhana/lodimages/%i/%i_%i_%i_%i.ppm",i,i,x,y,loddiv);
	    haslodfile = file_exists_name(tmp_s);
	    if ((haslodfile == 0) && (hastilefile == 0)) {
	      lodimage = image_new_rgb(lodxsize,lodysize);
	      image_scale(tileimage,lodimage);
	      image_save_file(lodimage,tmp_s);
	    }
	    li = lodimage_new(strdup(tmp_s));
	    lodimage_set_size(li,lodxsize,lodysize);
	    lodimage_set_scale(li,(float)loddiv);
	    tileimage_set_lodimage(ti,lodlevel,li);
	    if ((haslodfile == 0) && (hastilefile == 0)) {
	      image_free(lodimage);
	    }
	  }
	  tileimage_set_numlodimages(ti,5);
	  if (hastilefile == 0) {
	    image_free(tileimage);
	  }

	  geometryimage_add_tileimage(gi,ti);

	}
      }
      image_free(origimage);
    }
  }
}

#if 0
// Case 2:
// First create LODs for the original. Then tile the LODs.
void create_tiles_and_lods2(void *pp)
{
  ty_viewer *p;
  ty_imagegraph *ig;
  ty_geometryimage *gi;
  ty_tileimage *ti;
  int i;
  int r;
  float rx;
  float ry;
  void *origimage;
  void *tileimage;
  void *lodimage;
  void *li;
  int loddiv;
  int lodlevel;
  int x,y;
  int tilexsize,tileysize;
  int lodxsize,lodysize;
  int hastilefile,haslodfile;

  p = pp;
  ig = p->imagegraph;

  for (i = 0; i < ig->numimages; i++) {
    gi = ig->images[i];
    origimage = openimage(gi->filename);
    origxsize = image_get_xsize(origimage);
    origysize = image_get_ysize(origimage);
    if (origimage != NULL) {
      geometryimage_set_size(gi,origxsize,origysize);

      // First LODs. Then tiles.

      loddiv = 1;
      for (lodlevel = 0; lodlevel <= 4; lodlevel++) {
	lodxsize = origxsize/loddiv;
	lodysize = origysize/loddiv;
	lodimage = image_new_rgb(lodxsize,lodysize);
	image_scale(origimage,lodimage);

	for (y = 0; y < lodysize; y += C_TILE_YSIZE) {
	  if (lodysize - y < C_TILE_YSIZE) {
	    tileysize = lodysize - y;
	  } else {
	    tileysize = C_TILE_YSIZE;
	  }
	  for (x = 0; x < lodxsize; x += C_TILE_XSIZE) {
	    if (lodxsize - x < C_TILE_XSIZE) {
	      tilexsize = lodxsize - x;
	    } else {
	      tilexsize = C_TILE_XSIZE;
	    }

	    sprintf(tmp_s,"/home/juhana/lodimages/%i/%i_%i_%i_%i.ppm",i,i,x,y,loddiv);
	    tileimage = image_new_rgb(tilexsize,tileysize);
	    image_copy_rectangle(lodimage,x,y,x+tilexsize-1,y+tileysize-1,tileimage,0,0);
	    image_save_file(tileimage,tmp_s);
	    ti = tileimage_new(strdup(tmp_s));
	    tileimage_set_size(ti,tilexsize,tileysize);
	    tileimage_set_pos(ti,x,y);

CONTINUE

	  }
	}
	image_free(lodimage);
	loddiv *= 2;
      }



	  // <image number>_<tile x>_<tile y>_<lod level>.ppm
	  sprintf(tmp_s,"/home/juhana/lodimages2/%i/%i_%i_%i_0.ppm",i,i,x,y);
	  hastilefile = file_exists_name(tmp_s);
	  if (hastilefile == 0) {
	    tileimage = image_new_rgb(tilexsize,tileysize);
	    image_copy_rectangle(lodimage,x,y,x+tilexsize-1,y+tileysize-1,tileimage,0,0);
	    image_save_file(tileimage,tmp_s);
	  }
	  ti = tileimage_new(strdup(tmp_s));
	  tileimage_set_size(ti,tilexsize,tileysize);
	  tileimage_set_pos(ti,x,y);

	  li = lodimage_new(tileimage_get_filename(ti));
	  lodimage_set_size(li,tilexsize,tileysize);
	  tileimage_set_lodimage(ti,0,li);

	  loddiv = 1;
	  for (lodlevel = 1; lodlevel <= 4; lodlevel++) {
	    loddiv *= 2;
	    lodxsize = tilexsize/loddiv;
	    lodysize = tileysize/loddiv;
	    sprintf(tmp_s,"/home/juhana/lodimages/%i/%i_%i_%i_%i.ppm",i,i,x,y,loddiv);
	    haslodfile = file_exists_name(tmp_s);
	    if ((haslodfile == 0) && (hastilefile == 0)) {
	      lodimage = image_new_rgb(lodxsize,lodysize);
	      image_scale(tileimage,lodimage);
	      image_save_file(lodimage,tmp_s);
	    }
	    li = lodimage_new(strdup(tmp_s));
	    lodimage_set_size(li,lodxsize,lodysize);
	    lodimage_set_scale(li,(float)loddiv);
	    tileimage_set_lodimage(ti,lodlevel,li);
	    if ((haslodfile == 0) && (hastilefile == 0)) {
	      image_free(lodimage);
	    }
	  }
	  tileimage_set_numlodimages(ti,5);
	  if (hastilefile == 0) {
	    image_free(tileimage);
	  }

	  geometryimage_add_tileimage(gi,ti);

	}
      }
      image_free(origimage);
    }
  }
}
#endif

#if 0
// Broken due tiles.
void create_lods(void *pp)
{
  ty_viewer *p;
  ty_imagegraph *ig;
  ty_geometryimage *gi;
  int i;
  int r;
  float rx;
  float ry;
  void *origimage;
  void *lodimage;
  void *li;
  int loddiv;
  int lodlevel;

  p = pp;
  ig = p->imagegraph;

  for (i = 0; i < ig->numimages; i++) {
    gi = ig->images[i];
    origimage = openimage(gi->filename);
    if (origimage != NULL) {
      geometryimage_set_size(gi,image_get_xsize(origimage),image_get_ysize(origimage));
      // sprintf(tmp_s,"/mnt/c/work/lodimages/%i_1.ppm",i);
      // image_save_file(origimage,tmp_s);
      li = lodimage_new(gi->filename);
      lodimage_set_size(li,image_get_xsize(origimage),image_get_ysize(origimage));
      geometryimage_set_lodimage(gi,0,li);
      loddiv = 1;
      for (lodlevel = 1; lodlevel <= 4; lodlevel++) {
	loddiv *= 2;
	lodimage = image_new_rgb(image_get_xsize(origimage)/loddiv,image_get_ysize(origimage)/loddiv);
	image_scale(origimage,lodimage);
	sprintf(tmp_s,"/home/juhana/lodimages/%i_%i.ppm",i,loddiv);
	image_save_file(lodimage,tmp_s);
	li = lodimage_new(strdup(tmp_s));
	lodimage_set_size(li,image_get_xsize(lodimage),image_get_ysize(lodimage));
	lodimage_set_scale(li,(float)loddiv);
	geometryimage_set_lodimage(gi,lodlevel,li);
	image_free(lodimage);
      }
      geometryimage_set_numlodimages(gi,5);
      image_free(origimage);
    }
  }
}
#endif

void compute_zoomscale(ty_viewer *p)
{
  float r;

  r = exp(log(p->maxzoomscale)/p->numzoomlevels);
  p->zoomscale = pow(r,(float)p->zoomlevel);
}


void compute_scale(ty_viewer *p)
{
  float xscale;
  float yscale;
  float scale;

  if (p->rendertype == 1) {
    p->scale = 4.0;
    return;
  }

  if (p->scalingtype == 0) {
    // Use the existing p->scale value.
  } else if (p->scalingtype == 1) {
    // Fit to window but do not enlarge.
    xscale = (float)image_get_xsize(p->image)/image_get_xsize(p->displayimage);
    yscale = (float)image_get_ysize(p->image)/image_get_ysize(p->displayimage);
    if (xscale < 1.0) xscale = 1.0; // else it is ok
    if (yscale < 1.0) yscale = 1.0; // else it is ok
    if (xscale > yscale) scale = xscale;
    else scale = yscale;

    p->scale = scale;
  } else if (p->scalingtype == 2) {
    // Always fit to window.
    xscale = (float)image_get_xsize(p->image)/image_get_xsize(p->displayimage);
    yscale = (float)image_get_ysize(p->image)/image_get_ysize(p->displayimage);
    // if (xscale < 1.0) xscale = 1.0; // else it is ok
    // if (yscale < 1.0) yscale = 1.0; // else it is ok
    if (xscale > yscale) scale = xscale;
    else scale = yscale;

    p->scale = scale;
  }
}

void update_display_whole(ty_viewer *p)
{
  p->dithx = 0;
  p->dithy = 0;
  gdk_draw_rgb_image_dithalign (p->da->window,
                                p->image_gc,
                                0,
                                0,
                                image_get_xsize(p->displayimage),
                                image_get_ysize(p->displayimage),
                                p->dithertype,
                                image_get_buffer(p->displayimage),
                                image_get_xsize(p->displayimage) * 3,
                                p->dithx, p->dithy);

#if 0
  gdk_gc_set_function (p->image_gc, GDK_INVERT);
  gdk_draw_line(p->da->window,p->image_gc,400,100,500,500);
  gdk_gc_set_function (p->image_gc, GDK_COPY);
#endif
}


void update_render_and_display_whole(ty_viewer *p)
{
#if 0
  clock_begin();
#endif

  nifrender_scene_render(p->nifrender);

#if 0
  clock_end();
  fprintf(stderr,"time to scale: ");
  // about 2.6 sec
  clock_print();

  clock_begin();
#endif
  p->dithx = 0;
  p->dithy = 0;
  gdk_draw_rgb_image_dithalign (p->da->window,
                                p->image_gc,
                                0,
                                0,
                                image_get_xsize(p->displayimage),
                                image_get_ysize(p->displayimage),
                                p->dithertype,
                                image_get_buffer(p->displayimage),
                                image_get_xsize(p->displayimage) * 3,
                                p->dithx, p->dithy);
#if 0
  clock_end();
  fprintf(stderr,"time to draw: ");
  // about 0.65 sec
  clock_print();
#endif

#if 0
  gdk_gc_set_function (p->image_gc, GDK_INVERT);
  gdk_draw_line(p->da->window,p->image_gc,400,100,500,500);
  gdk_gc_set_function (p->image_gc, GDK_COPY);
#endif
}

#if 0
// Not needed because we don't use compute_scale().

void update_render_and_display_whole_noscales(ty_viewer *p)
{
  image_scale_zoom(p->image,p->displayimage,p->scale*p->zoomscale,p->xcenter,p->ycenter);
  p->dithx = 0;
  p->dithy = 0;

  gdk_draw_rgb_image_dithalign (p->da->window,
                                p->image_gc,
                                0,
                                0,
                                image_get_xsize(p->displayimage),
                                image_get_ysize(p->displayimage),
                                p->dithertype,
                                image_get_buffer(p->displayimage),
                                image_get_xsize(p->displayimage) * 3,
                                p->dithx, p->dithy);
}
#endif

void update_display_area(ty_viewer *p,int xmin,int ymin,int xmax,int ymax)
{
  // fprintf(stderr,"before update_display_area\n");
  gdk_draw_rgb_image_dithalign (p->da->window,
                                p->image_gc,
#if 0
                                0,
                                0,
                                image_get_xsize(p->displayimage),
                                image_get_ysize(p->displayimage),
#endif
				xmin,
				ymin,
				xmax-xmin+1,
				ymax-ymin+1,
                                p->dithertype,
                                // image_get_buffer(p->displayimage),
                                image_get_buffer(p->displayimage)+image_get_xsize(p->displayimage) * 3*ymin + 3*xmin,
                                image_get_xsize(p->displayimage) * 3,
                                p->dithx, p->dithy);
}

void display_copy(ty_viewer *p,int xmin,int ymin,int xmax,int ymax,
		  int destxmin, int destymin)
{
  // fprintf(stderr,"before display_copy\n");
  gdk_window_copy_area(p->da->window,
		       p->image_gc,
		       destxmin,
		       destymin,
		       p->da->window,
		       xmin,
		       ymin,
		       xmax-xmin+1,
		       ymax-ymin+1);
}

void settopwindowtitle(ty_viewer *p)
{
  if (p->rendertype == 1) {
    strncpy(p->topwindowtitle,"Imagegraph",60);
    gtk_window_set_title (GTK_WINDOW(p->topwindow), p->topwindowtitle);
    return;
  }

  strncpy(p->topwindowtitle,p->filenames[p->currentfile],60);
  gtk_window_set_title (GTK_WINDOW(p->topwindow), p->topwindowtitle);
}


// XXXX was empty for rgbimage version
// Create a new backing pixmap of the appropriate size.
static gint
configure_event (GtkWidget *widget, GdkEventConfigure *event, gpointer gp)
{
  ty_viewer *p;

  p = gp;

  // fprintf(stderr,"allocation xsize = %i\n",(int)widget->allocation.width);
  // fprintf(stderr,"allocation ysize = %i\n",(int)widget->allocation.height);

  // Resize the RGB image here.
  // XXXX Currently we are drawing the p->image directly, but
  // we should compute and display p->rgbimage from p->image.
  if (p->displayimage != NULL) {
    image_free(p->displayimage);
    image_free(p->tmpdisplayimage);
    // nifrender_free(p->nifrender);
  }

  p->displayimage = image_new_rgb((gint)widget->allocation.width,
				  (gint)widget->allocation.height);
  p->tmpdisplayimage = image_new_rgb((gint)widget->allocation.width,
				     (gint)widget->allocation.height);

  // XXXX This causes model loading. It is wrong.
  p->nifrender = nifrender_new(p->displayimage);
  nifrender_set_fillfactor(p->nifrender,p->fillfactor);

  // No clear needed because we render the whole display.

  p->display_xsize = (int)widget->allocation.width;
  p->display_ysize = (int)widget->allocation.height;

  compute_scale(p);

#if 0
  // Caused trouble. This is now done in expose.
  update_render_and_display_whole(p);
#endif

  p->isconfigure = 1;

  return TRUE;
}

static gint
expose_event (GtkWidget *widget, GdkEventExpose *event, gpointer gp)
{
  ty_viewer *p;

  p = gp;

  // fprintf(stderr,"expose area min/max = %i %i %i %i\n",event->area.x, event->area.y,event->area.x+(int)event->area.width-1,event->area.y+(int)event->area.height-1);

  // Add expose area to here.
  // update_display_area(p,event->area.x, event->area.y,event->area.x+(int)event->area.width-1,event->area.y+(int)event->area.height-1);

#if 0
  if (p->isconfigure == 1) {
    update_render_and_display_whole(p);
    p->isconfigure = 0;
  } else {
    // The display image gets corrupted when the image is moved.
    // This reveals all the display image.
    update_display_whole(p);
  }
#endif

  if (p->isconfigure == 1) {
    update_render_and_display_whole(p);
    p->isconfigure = 0;
  } else {
    update_render_and_display_whole(p);
  }

#if 0
  gdk_draw_pixmap(widget->window,
                  widget->style->fg_gc[GTK_WIDGET_STATE (widget)],
                  p->pixmap,
                  event->area.x, event->area.y,
                  event->area.x, event->area.y,
                  (gint)event->area.width, (gint)event->area.height);
#endif

  return FALSE;
}

static gint
viewer_button_press_event (GtkWidget *widget, GdkEventButton *event, gpointer gp)
{
  ty_viewer *p;
  ty_imagegraph *qq;
  ty_imagegraph *ig;
  ty_geometryimage *q;
  ty_geometryimage *gi;
  int i;
  int axmin,aymin,axmax,aymax;
  ty_bound b1;
  ty_bound b2;

  p = (ty_viewer *)gp;

  // fprintf(stderr,"press at %f, %f\n",event->x,event->y);

  // We should check what we are doing currently.
  // Zoom may work even if we are moving.

  if (event->button == 1) {
    if (event->state & GDK_CONTROL_MASK) {
      p->moving = 3;
      p->movexstart = event->x;
      p->moveystart = event->y;
      p->movexprev = event->x;
      p->moveyprev = event->y;
    } else {
      p->moving = 1;
      p->movexstart = event->x;
      p->moveystart = event->y;
      p->movexprev = event->x;
      p->moveyprev = event->y;
      nifrender_set_fillfactor(p->nifrender,p->movefillfactor);
      update_render_and_display_whole(p);

    }
  }

  if (event->button == 3) {
    if (event->state & GDK_CONTROL_MASK) {
      p->moving = 2;
      p->movexstart = event->x;
      p->moveystart = event->y;
      p->movexprev = event->x;
      p->moveyprev = event->y;
    } else {
      p->moving = 4;
      p->movexstart = event->x;
      p->moveystart = event->y;
      p->movexprev = event->x;
      p->moveyprev = event->y;

      // p->move_start_zscr = nifrender_get_zscr(p->nifrender);
      nifrender_command_return(p->nifrender,"get zscr",cmd_return);
      p->move_start_zscr = atof(cmd_return);


      nifrender_set_fillfactor(p->nifrender,p->movefillfactor);
      update_render_and_display_whole(p);
    }
  }

#if 0
  if (event->button == 1) {
    if (p->rendertype == 0) {
      p->zoomlevel++;
      if (p->zoomlevel > p->numzoomlevels) {
	p->zoomlevel = p->numzoomlevels;
      } else {
	p->xcenter = ((float)event->x - (float)image_get_xsize(p->displayimage)/2.0)*(p->scale*p->zoomscale) + p->xcenter;
	p->ycenter = ((float)event->y - (float)image_get_ysize(p->displayimage)/2.0)*(p->scale*p->zoomscale) + p->ycenter;
	update_render_and_display_whole(p);
      }
    } else if (p->rendertype == 1) {
      imagegraph_set_pos(p->imagegraph,
			 imagegraph_get_xpos(p->imagegraph) - (float)event->x + (float)image_get_xsize(p->displayimage)/2.0,
			 imagegraph_get_ypos(p->imagegraph) - (float)event->y + (float)image_get_ysize(p->displayimage)/2.0);
      update_render_and_display_whole(p);
    }
  } else if (event->button == 2) {
    if (event->state & GDK_CONTROL_MASK) {
      // Should test for rendertype == 2 but we implement the single
      // image viewer with the multi image viewer.
      p->moving = 2;
      p->movexstart = event->x;
      p->moveystart = event->y;
      p->movexprev = event->x;
      p->moveyprev = event->y;
      // What image we will be moving?
      qq = p->imagegraph;
      for (i = 0; i < qq->numimages; i++) {
	q = qq->images[i];
	gi = q;
	ig = qq;

	b1.xmin = 0.0;
	b1.ymin = 0.0;
	b1.xmax = (float)gi->xsize;
	b1.ymax = (float)gi->ysize;
	geometryimage_gi2ig_bound(gi,&b1,&b2);
	imagegraph_ig2disp_bound(ig,&b2,&b1);

	axmin = b1.xmin;
	aymin = b1.ymin;
	axmax = b1.xmax;
	aymax = b1.ymax;

	if ((p->movexstart >= axmin) && (p->movexstart <= axmax) && (p->moveystart >= aymin) && (p->moveystart <= aymax)) {
	  p->moveimageindex = i;
	  fprintf(stderr,"hit the image %s\n",q->filename);
	}
      }
    } else {
      p->moving = 1;
      p->movexstart = event->x;
      p->moveystart = event->y;
      p->movexprev = event->x;
      p->moveyprev = event->y;
    }
  } else if (event->button == 3) {
    p->zoomlevel--;
    if (p->zoomlevel < 0) {
      p->zoomlevel = 0;
    } else {
      p->xcenter = ((float)event->x - (float)image_get_xsize(p->displayimage)/2.0)*(p->scale*p->zoomscale) + p->xcenter;
      p->ycenter = ((float)event->y - (float)image_get_ysize(p->displayimage)/2.0)*(p->scale*p->zoomscale) + p->ycenter;
      update_render_and_display_whole(p);
    }
  }

#endif

  return TRUE;
}

static gint
viewer_button_release_event (GtkWidget *widget, GdkEventButton *event, gpointer gp)
{
  ty_viewer *p;

  p = (ty_viewer *)gp;

  // fprintf(stderr,"release at %f, %f\n",event->x,event->y);

  // Back-spin with sparse rendering.
  if (p->moving == 1) {
    p->moving = 0;
    nifrender_set_fillfactor(p->nifrender,p->fillfactor);
    update_render_and_display_whole(p);
  }

  // Back-spin with full rendering.
  if (p->moving == 2) {
    p->moving = 0;
  }

  // XY-movement.
  if (p->moving == 3) {
    p->moving = 0;
    nifrender_set_fillfactor(p->nifrender,p->fillfactor);
    update_render_and_display_whole(p);
  }

  // Forward-backward.
  if (p->moving == 4) {
    p->moving = 0;
    nifrender_set_fillfactor(p->nifrender,p->fillfactor);
    update_render_and_display_whole(p);
  }

  return TRUE;
}

#if 0
// Not as long as Ubuntu has GTK 1.2 only!!
static gint
viewer_scroll_event (GtkWidget *widget, GdkEventScroll *event, gpointer gp)
{
  ty_viewer *p;

  p = (ty_viewer *)gp;

  // fprintf(stderr,"release at %f, %f\n",event->x,event->y);

  if (p->moving == 1) {
    p->moving = 0;
    nifrender_set_fillfactor(p->nifrender,p->fillfactor);
    update_render_and_display_whole(p);
  }

  if (p->moving == 2) {
    p->moving = 0;
  }

  return TRUE;
}
#endif

int opennextimage(ty_viewer *p)
{
  int lastshown;

  lastshown = p->currentfile;
  // Free the previous image.
  if (lastshown != -1) {
    image_free(p->image);
  }
  p->currentfile++;
  while (p->currentfile < p->numfiles) {
    // Open the next image.
    p->image = openimage(p->filenames[p->currentfile]);
    if (p->image != NULL) return 1;
    p->currentfile++;
  }
  p->currentfile = lastshown;
  if (p->currentfile != -1) {
    p->image = openimage(p->filenames[p->currentfile]);
  } else {
    return 0;
  }

  return 1;
}

int openprevimage(ty_viewer *p)
{
  int lastshown;

  lastshown = p->currentfile;
  // Free the previous image.
  if (lastshown != -1) {
    image_free(p->image);
  }
  p->currentfile--;
  while (p->currentfile >= 0) {
    // Open the next image.
    p->image = openimage(p->filenames[p->currentfile]);
    if (p->image != NULL) return 1;
    p->currentfile--;
  }
  p->currentfile = lastshown;
  if (p->currentfile != -1) {
    p->image = openimage(p->filenames[p->currentfile]);
  } else {
    return 0;
  }

  return 1;
}

#if 1
static gint
viewer_key_press_event (GtkWidget *widget, GdkEventKey *event, gpointer gp)
{
  ty_viewer *p;
  int x, y;
  GdkModifierType state;
  float xmove;
  float ymove;
  int numscenes;
  int current_scene;

  p = (ty_viewer *)gp;

  // fprintf(stderr,"key press: %s\n",event->string);

  gdk_window_get_pointer (event->window, &x, &y, &state);
  // fprintf(stderr,"key = %i, %i\n",x,y);

  xmove = (float)image_get_xsize(p->displayimage)/4.0*p->zoomscale;
  ymove = (float)image_get_ysize(p->displayimage)/4.0*p->zoomscale;

  if (strcmp(event->string,"n") == 0) {
    // nifrender_lego_next(p->nifrender);
    nifrender_command(p->nifrender,"next lego brick");
    update_render_and_display_whole(p);
  } else if (strcmp(event->string,"b") == 0) {
    // nifrender_lego_prev(p->nifrender);
    nifrender_command(p->nifrender,"prev lego brick");
    update_render_and_display_whole(p);
  } else if (strcmp(event->string,"s") == 0) {
    nifrender_command_return(p->nifrender,"get numscenes",cmd_return);
    numscenes = atoi(cmd_return);
    nifrender_command_return(p->nifrender,"get current scene",cmd_return);
    current_scene = atoi(cmd_return);
    current_scene++;
    if (current_scene == numscenes) current_scene = 0;
    sprintf(cmd_send,"set current scene %i",current_scene);
    nifrender_command(p->nifrender,cmd_send);
    update_render_and_display_whole(p);
  } else if (strcmp(event->string,"q") == 0) {
    // XXXX Call viewer_quit() which frees all malloced memories.
    gtk_main_quit();
  }


  return TRUE;
}
#endif


static gint
viewer_key_release_event (GtkWidget *widget, GdkEventKey *event, gpointer gp)
{
  ty_viewer *p;
  int x, y;
  GdkModifierType state;

  p = (ty_viewer *)gp;

  // Why this prints null?
  // fprintf(stderr,"key release: %s\n",event->string);
  gdk_window_get_pointer (event->window, &x, &y, &state);
  // fprintf(stderr,"key = %i, %i\n",x,y);

  return TRUE;
}

static gint
viewer_motion_notify_event (GtkWidget *widget, GdkEventMotion *event, gpointer gp)
{
  int x, y;
  GdkModifierType state;
  ty_viewer *p;
  int int_xmin;
  int int_xmax;
  int int_ymin;
  int int_ymax;
  int areaxmin;
  int areaxmax;
  int areaymin;
  int areaymax;
  ty_imagegraph *qq;
  ty_geometryimage *q;
  int axmin,aymin,axmax,aymax;
  int bxmin,bymin,bxmax,bymax;
  ty_imagegraph *ig;
  ty_geometryimage *gi;
  ty_bound b1;
  ty_bound b2;
  float zscr,back,spin;
  int dy;
  int i;

  p = (ty_viewer *)gp;

  if (event->is_hint) {
    gdk_window_get_pointer (event->window, &x, &y, &state);
    event->x = x;
    event->y = y;
    event->state = state;
#if 1
  }
#else
    fprintf(stderr,"motion notify is hint\n");
  } else {
    fprintf(stderr,"motion notify is not hint\n");
  }
#endif

  if (p->moving == 1) {
    p->movex = event->x;
    p->movey = event->y;
    p->movedx = p->movex - p->movexprev;
    p->movedy = p->movey - p->moveyprev;
    p->movexprev = p->movex;
    p->moveyprev = p->movey;

    // back = nifrender_get_back(p->nifrender);
    nifrender_command_return(p->nifrender,"get back",cmd_return);
    back = atof(cmd_return);
    // spin = nifrender_get_spin(p->nifrender);
    nifrender_command_return(p->nifrender,"get spin",cmd_return);
    spin = atof(cmd_return);

    back += 0.5*p->movedy;
    spin -= 0.5*p->movedx;

    // nifrender_set_back(p->nifrender,back);
    sprintf(cmd_send,"set back %f",back);
    nifrender_command(p->nifrender,cmd_send);
    // nifrender_set_spin(p->nifrender,spin);
    sprintf(cmd_send,"set spin %f",spin);
    nifrender_command(p->nifrender,cmd_send);


    nifrender_set_fillfactor(p->nifrender,p->movefillfactor);
    update_render_and_display_whole(p);
  }

  if (p->moving == 2) {
    p->movex = event->x;
    p->movey = event->y;
    p->movedx = p->movex - p->movexprev;
    p->movedy = p->movey - p->moveyprev;
    p->movexprev = p->movex;
    p->moveyprev = p->movey;

    // back = nifrender_get_back(p->nifrender);
    nifrender_command_return(p->nifrender,"get back",cmd_return);
    back = atof(cmd_return);
    // spin = nifrender_get_spin(p->nifrender);
    nifrender_command_return(p->nifrender,"get spin",cmd_return);
    spin = atof(cmd_return);

    back += 0.5*p->movedy;
    spin -= 0.5*p->movedx;

    // nifrender_set_back(p->nifrender,back);
    sprintf(cmd_send,"set back %f",back);
    nifrender_command(p->nifrender,cmd_send);
    // nifrender_set_spin(p->nifrender,spin);
    sprintf(cmd_send,"set spin %f",spin);
    nifrender_command(p->nifrender,cmd_send);

    nifrender_set_fillfactor(p->nifrender,p->fillfactor);
    update_render_and_display_whole(p);
  }

  if (p->moving == 4) {
    p->movex = event->x;
    p->movey = event->y;
    p->movedx = p->movex - p->movexprev;
    p->movedy = p->movey - p->moveyprev;
    p->movexprev = p->movex;
    p->moveyprev = p->movey;

    dy = p->moveystart - p->movey;
    if (dy < 0) {
      zscr = p->move_start_zscr;
      for (i = 0; i < -dy; i++) {
	// We need some kind of min step.
	zscr *= 0.8;
      }
    } else {
      zscr = p->move_start_zscr;
      for (i = 0; i < dy; i++) {
	zscr *= 1.0/0.8;
      }
    }

#if 0
    zscr = p->move_start_zscr*exp(0.1*dy);
    if (zscr < 1.0) zscr = 1.0;
#endif
#if 0
    step = p->move_start_zscr/10.0;
    if (step == 0.0) step = 0.1;
    zscr = p->move_start_zscr + step*dy;
#endif

    // nifrender_set_zscr(p->nifrender,zscr);
    sprintf(cmd_send,"set zscr %f",zscr);
    nifrender_command(p->nifrender,cmd_send);

    nifrender_set_fillfactor(p->nifrender,p->movefillfactor);
    update_render_and_display_whole(p);
  }

#if 0
  if (p->moving == 1) {
    p->movex = event->x;
    p->movey = event->y;
    p->movedx = p->movex - p->movexprev;
    p->movedy = p->movey - p->moveyprev;
    // fprintf(stderr,"image is moving at %i %i by %i %i\n",(int)(event->x),(int)(event->y),p->movedx,p->movedy);
    p->movexprev = p->movex;
    p->moveyprev = p->movey;

    // Now: Move image by copying the display RGB image.
    // ok Later: Move image by copying the drawing area.

    if ((p->movedx != 0) || (p->movedy != 0)) {

#if 1
      // This does not work, but it is not bad if we fail to find
      // the correct way.
      p->dithx += p->movedx;
      p->dithy += p->movedy;
#endif
#if 0
      // This does not work, but it is not bad if we fail to find
      p->dithx -= p->movedx;
      p->dithy -= p->movedy;
#endif

      compute_scale(p);
      compute_zoomscale(p);

      // Intersection of the screen and the moved.

      // int_xmin = max(0,p->movedx);
      if (p->movedx > 0)
	int_xmin = p->movedx;
      else
	int_xmin = 0;

      // int_xmax = min(xsize-1,xsize-1+p->movedx)
      // This sieves to (p->movedx > 0) and can be merged above.
      if (image_get_xsize(p->displayimage)-1+p->movedx > image_get_xsize(p->displayimage)-1)
	int_xmax = image_get_xsize(p->displayimage)-1;
      else
	int_xmax = image_get_xsize(p->displayimage)-1+p->movedx;

      // int_ymin = max(0,p->movedy);
      if (p->movedy > 0)
	int_ymin = p->movedy;
      else
	int_ymin = 0;

      // int_ymax = min(ysize-1,ysize-1+p->movedy)
      if (image_get_ysize(p->displayimage)-1+p->movedy > image_get_ysize(p->displayimage)-1)
	int_ymax = image_get_ysize(p->displayimage)-1;
      else
	int_ymax = image_get_ysize(p->displayimage)-1+p->movedy;

#if 0
      image_copy_rectangle(p->displayimage,int_xmin-p->movedx,int_ymin-p->movedy,int_xmax-p->movedx,int_ymax-p->movedy,p->tmpdisplayimage,int_xmin,int_ymin);
      image_copy_rectangle(p->tmpdisplayimage,int_xmin,int_ymin,int_xmax,int_ymax,p->displayimage,int_xmin,int_ymin);
#else
      display_copy(p,int_xmin-p->movedx,int_ymin-p->movedy,int_xmax-p->movedx,int_ymax-p->movedy,int_xmin,int_ymin);
#endif

      if (p->rendertype == 0) {
	p->xcenter -= p->movedx*p->scale*p->zoomscale;
	p->ycenter -= p->movedy*p->scale*p->zoomscale;
      } else if (p->rendertype == 1) {
	imagegraph_set_pos(p->imagegraph,
			   imagegraph_get_xpos(p->imagegraph) + p->movedx,
			   imagegraph_get_ypos(p->imagegraph) + p->movedy);
      }

      if (p->movedx == 0) {
	// No LR area.
      } else if (p->movedx > 0) {
	// lrarea = 0 0 p->movedx-1 ysize-1
	areaxmin = 0;
	areaymin = 0;
	areaxmax = p->movedx-1;
	areaymax = image_get_ysize(p->displayimage)-1;

	if (p->rendertype == 0) {
	  image_scale_zoom_area(p->image,p->displayimage,p->scale*p->zoomscale,p->xcenter,p->ycenter,areaxmin,areaymin,areaxmax,areaymax);
	  update_display_area(p,areaxmin,areaymin,areaxmax,areaymax);
	} else if (p->rendertype == 1) {
	  imagegraph_render_area(p->imagegraph,p->displayimage,p->scale*p->zoomscale,p->xcenter,p->ycenter,areaxmin,areaymin,areaxmax,areaymax);
	  update_display_area(p,areaxmin,areaymin,areaxmax,areaymax);
	}
      } else if (p->movedx < 0) {
	// lrarea = xsize-1-(-p->movedx-1) 0 xsize-1 ysize-1
	areaxmin = image_get_xsize(p->displayimage)-1-(-p->movedx-1);
	areaymin = 0;
	areaxmax = image_get_xsize(p->displayimage)-1;
	areaymax = image_get_ysize(p->displayimage)-1;
	if (p->rendertype == 0) {
	  image_scale_zoom_area(p->image,p->displayimage,p->scale*p->zoomscale,p->xcenter,p->ycenter,areaxmin,areaymin,areaxmax,areaymax);
	  update_display_area(p,areaxmin,areaymin,areaxmax,areaymax);
	} else if (p->rendertype == 1) {
	  imagegraph_render_area(p->imagegraph,p->displayimage,p->scale*p->zoomscale,p->xcenter,p->ycenter,areaxmin,areaymin,areaxmax,areaymax);
	  update_display_area(p,areaxmin,areaymin,areaxmax,areaymax);
	}
      }

      if (p->movedy == 0) {
	// No TB area.
      } else if (p->movedy > 0) {
	// tbarea = int_xmin 0 int_xmax p->movedy-1
	areaxmin = int_xmin;
	areaymin = 0;
	areaxmax = int_xmax;
	areaymax = p->movedy-1;
	if (p->rendertype == 0) {
	  image_scale_zoom_area(p->image,p->displayimage,p->scale*p->zoomscale,p->xcenter,p->ycenter,areaxmin,areaymin,areaxmax,areaymax);
	  update_display_area(p,areaxmin,areaymin,areaxmax,areaymax);
	} else if (p->rendertype == 1) {
	  imagegraph_render_area(p->imagegraph,p->displayimage,p->scale*p->zoomscale,p->xcenter,p->ycenter,areaxmin,areaymin,areaxmax,areaymax);
	  update_display_area(p,areaxmin,areaymin,areaxmax,areaymax);
	}
      } else if (p->movedy < 0) {
	// tbarea = int_xmin ysize-1-(-p->movedy-1) int_xmax ysize-1
	areaxmin = int_xmin;
	areaymin = image_get_ysize(p->displayimage)-1-(-p->movedy-1);
	areaxmax = int_xmax;
	areaymax = image_get_ysize(p->displayimage)-1;
	if (p->rendertype == 0) {
	  image_scale_zoom_area(p->image,p->displayimage,p->scale*p->zoomscale,p->xcenter,p->ycenter,areaxmin,areaymin,areaxmax,areaymax);
	  update_display_area(p,areaxmin,areaymin,areaxmax,areaymax);
	} else if (p->rendertype == 1) {
	  imagegraph_render_area(p->imagegraph,p->displayimage,p->scale*p->zoomscale,p->xcenter,p->ycenter,areaxmin,areaymin,areaxmax,areaymax);
	  update_display_area(p,areaxmin,areaymin,areaxmax,areaymax);
	}
      }

    }
  }

  if (p->moving == 2) {
    p->movex = event->x;
    p->movey = event->y;
    p->movedx = p->movex - p->movexprev;
    p->movedy = p->movey - p->moveyprev;
    // fprintf(stderr,"image is moving at %i %i by %i %i\n",(int)(event->x),(int)(event->y),p->movedx,p->movedy);
    p->movexprev = p->movex;
    p->moveyprev = p->movey;

    // Now: Move image by copying the display RGB image.
    // ok Later: Move image by copying the drawing area.

    if ((p->movedx != 0) || (p->movedy != 0)) {

      compute_scale(p);
      compute_zoomscale(p);

      qq = p->imagegraph;
      q = qq->images[p->moveimageindex];

      ig = qq;
      gi = q;

      b1.xmin = 0.0;
      b1.ymin = 0.0;
      b1.xmax = (float)gi->xsize;
      b1.ymax = (float)gi->ysize;
      geometryimage_gi2ig_bound(gi,&b1,&b2);
      imagegraph_ig2disp_bound(ig,&b2,&b1);

      axmin = b1.xmin;
      aymin = b1.ymin;
      axmax = b1.xmax;
      aymax = b1.ymax;

      // Move the image.
      gi->xpos += p->movedx/ig->scale;
      gi->ypos += p->movedy/ig->scale;

      // Area of the moved image.
      b1.xmin = 0.0;
      b1.ymin = 0.0;
      b1.xmax = (float)gi->xsize;
      b1.ymax = (float)gi->ysize;
      geometryimage_gi2ig_bound(gi,&b1,&b2);
      imagegraph_ig2disp_bound(ig,&b2,&b1);

      bxmin = b1.xmin;
      bymin = b1.ymin;
      bxmax = b1.xmax;
      bymax = b1.ymax;

      // Union of the areas A and B.
      if (axmin < bxmin) areaxmin = axmin;
      else areaxmin = bxmin;
      if (aymin < bymin) areaymin = aymin;
      else areaymin = bymin;
      if (axmax > bxmax) areaxmax = axmax;
      else areaxmax = bxmax;
      if (aymax > bymax) areaymax = aymax;
      else areaymax = bymax;

      if (areaxmin < 0) areaxmin = 0;
      if (areaymin < 0) areaymin = 0;
      if (areaxmax > image_get_xsize(p->displayimage)-1) areaxmax = image_get_xsize(p->displayimage)-1;
      if (areaymax > image_get_ysize(p->displayimage)-1) areaymax = image_get_ysize(p->displayimage)-1;

      imagegraph_render_area(p->imagegraph,p->displayimage,1.0,0.0,0.0,areaxmin,areaymin,areaxmax,areaymax);
      update_display_area(p,areaxmin,areaymin,areaxmax,areaymax);

    }

  }
#endif

  return TRUE;
}

#if 0
static gint
openglda_enter_notify_event (GtkWidget *widget, GdkEventCrossing *event, gpointe
r gp)
{
  int x, y;
  GdkModifierType state;
  ty_openglda *p;
  int r;

  p = (ty_openglda *)gp;

  // fprintf(stderr,"enter1\n");

  r = 0;
  if (p->callbacks_func[GDK_ENTER_NOTIFY] != NULL)
    r = (p->callbacks_func[GDK_ENTER_NOTIFY])(widget, event, p->callbacks_funcda
ta[GDK_ENTER_NOTIFY]);

  if (r)
    gdk_window_invalidate_rect (widget->window, &widget->allocation, FALSE);

  return TRUE;
}

static gint
openglda_leave_notify_event (GtkWidget *widget, GdkEventCrossing *event, gpointe
r gp)
{
  int x, y;
  GdkModifierType state;
  ty_openglda *p;
  int r;

  p = (ty_openglda *)gp;

  // fprintf(stderr,"leave1\n");

  r = 0;
  if (p->callbacks_func[GDK_LEAVE_NOTIFY] != NULL)
    r = (p->callbacks_func[GDK_LEAVE_NOTIFY])(widget, event, p->callbacks_funcda
ta[GDK_LEAVE_NOTIFY]);

  if (r)
    gdk_window_invalidate_rect (widget->window, &widget->allocation, FALSE);

  return TRUE;
}
#endif



void call_viewer_destroy(GtkWidget *widget, gpointer data)
{
  ty_viewer *p;

  p = data;
  // mmapfile_close(p->mmap);
  free(p);

  gtk_main_quit();
}

void call_viewer_quit(GtkWidget *widget, gpointer data)
{
  ty_viewer *p;

  p = data;
  // mmapfile_close(p->mmap);
  free(p);

  gtk_main_quit();
}


// XXXX We need dither aligned image display routine for displaying
// a large image and for displaying a tiled large image.

// This is the routine which we will use for displaying a part of
// the image. The image displayed is possibly composed from
// tiles or otherwise manipulated.
// XXXX Tiling as graph node.
// non-tiled image --> tiled image (cached to disk)
// Tiled image file format: all in the same file, or tiles in
// separate files, or a mix of both.

// When the image is grabbed and moved, only the exposed pixels
// need to be recomputed. Other pixels may be copied.
// (As done in my "waver.c".)


// from gimp/app/colormaps.c

#endif

void call_espbrowser_destroy(GtkWidget *widget, gpointer data)
{
  ty_espbrowser *p;

  p = data;
  // mmapfile_close(p->mmap);
  free(p);

  gtk_main_quit();
}

#if 0

GdkVisual *g_visual = NULL;
GdkColormap *g_cmap = NULL;

void get_standard_colormaps()
{
  int min_colors;

  min_colors = 144;
  min_colors = 240;

  gdk_rgb_set_min_colors(min_colors);
  gdk_rgb_set_install(0);

  g_visual = gdk_rgb_get_visual ();
  g_cmap   = gdk_rgb_get_cmap ();

  gtk_widget_set_default_visual (g_visual);
  gtk_widget_set_default_colormap (g_cmap);

}
#endif



int main(int ac, char **av)
{
  ty_espbrowser *p;
  GtkWidget *box;
  GtkWidget *textview;
  GtkWidget *sw;
  int i;
  GtkTextBuffer *textbuffer;
  GtkTextIter textiter;

  gtk_init(&ac, &av);

  if (ac != 2) {
    fprintf(stderr,"Usage: espbrowser <espfile>\n");
    exit(-1);
  }

  p = (ty_espbrowser *)malloc(sizeof(ty_espbrowser));
  p->moving = 0;
  p->isconfigure = 1;
  p->dithertype = GDK_RGB_DITHER_MAX;
  p->dithx = 0;
  p->dithy = 0;
  p->topwindowtitle = (char *)malloc(61*sizeof(char));
  p->rendertype = 1;

  // Moved to configure callback.
  // p->nifrender = nifrender_new();

#if 0
  p->back = -90.0;
  p->spin = 0.0;
#endif

  // XXXX Move to scene.
  p->fillfactor = 1.0;
  p->movefillfactor = 0.2;
  p->movefillfactor = 0.02;

#if 0
  p->random = random_new(462547);
#endif

  p->topwindow_xsize = gdk_screen_width() * 0.80;
  p->topwindow_ysize = gdk_screen_height() * 0.80;
  p->display_xsize = 20;
  p->display_ysize = 20;

  // The RGB image which matches the displayed GDK pixmap.
  // Zoomed image is cropped to this RGB image.
  // This image needs to be replaced when the window size is changed.
  // p->rgbimage = rgbimage_new(p->screenwindow_xsize,p->screenwindow_ysize);
#if 0
  p->displayimage = image_new_rgb(p->display_xsize,p->display_ysize);
  p->tmpdisplayimage = image_new_rgb(p->display_xsize,p->display_ysize);
#endif

  p->topwindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  // XXXX gtk_window_set_screen() ??!?
  gtk_window_set_default_size(GTK_WINDOW(p->topwindow),p->topwindow_xsize, p->topwindow_ysize);

  sprintf(p->topwindowtitle,"ESP Browser");
  gtk_window_set_title (GTK_WINDOW(p->topwindow), p->topwindowtitle);
  // XXXX  gtk_container_set_border_width (GTK_CONTAINER (window), 0);

  gtk_signal_connect(GTK_OBJECT(p->topwindow), "destroy",
                     GTK_SIGNAL_FUNC(call_espbrowser_destroy), p);

  // Key events must be read from the top window.
  // I don't know why drawing area will not work.
  gtk_widget_set_events (p->topwindow, gtk_widget_get_events(p->topwindow)
			 | GDK_KEY_PRESS_MASK
                         | GDK_KEY_RELEASE_MASK);

  // XXXX Add key callbacks later.
#if 0
  gtk_signal_connect (GTK_OBJECT (p->topwindow), "key_press_event",
                      (GtkSignalFunc) viewer_key_press_event, (gpointer)p);

  gtk_signal_connect (GTK_OBJECT (p->topwindow), "key_release_event",
                      (GtkSignalFunc) viewer_key_release_event, (gpointer)p);
#endif

  box = gtk_vbox_new(FALSE, 0);

#if 0
  p->button = gtk_button_new_with_label("Quit");
  gtk_signal_connect(GTK_OBJECT(p->button), "clicked",
		     GTK_SIGNAL_FUNC(call_viewer_quit),
		     (gpointer)p);
  gtk_box_pack_start(GTK_BOX(box), p->button, FALSE, FALSE, 0);
  gtk_widget_show(p->button);
#endif

  // Add text widget here.
  textview = gtk_text_view_new ();
  textbuffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (textview));
      
  gtk_text_buffer_get_iter_at_offset (textbuffer, &textiter, 0);

  gtk_text_buffer_insert (textbuffer, &textiter, "The text widget can display text with all kinds of nifty attributes. It also supports multiple views of the same buffer; this demo is showing the same buffer in two places.\n\n", -1);

  gtk_text_buffer_insert (textbuffer, &textiter, "The text widget can display text with all kinds of nifty attributes. It also supports multiple views of the same buffer; this demo is showing the same buffer in two places.\n\n", -1);



  sw = gtk_scrolled_window_new (NULL, NULL);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (sw),
				  GTK_POLICY_AUTOMATIC,
				  GTK_POLICY_AUTOMATIC);

  gtk_container_add (GTK_CONTAINER (sw), textview);


  gtk_box_pack_start (GTK_BOX (box), sw, TRUE, TRUE, 0);

  gtk_widget_show_all (sw);


#if 0
  p->da = gtk_drawing_area_new();

  // This gives the minimum size for the window.
  // I don't know why the window cannot be made smaller
  // The DA is soon resized to fit the top window! The size 10x10
  // is never used.
  gtk_drawing_area_size (GTK_DRAWING_AREA (p->da), 10, 10);

  gtk_box_pack_start (GTK_BOX (box), p->da, TRUE, TRUE, 0);


  gtk_widget_set_events (p->da, gtk_widget_get_events(p->da)
                         | GDK_EXPOSURE_MASK
                         | GDK_LEAVE_NOTIFY_MASK
                         | GDK_ENTER_NOTIFY_MASK
                         | GDK_BUTTON_PRESS_MASK
                         | GDK_BUTTON_RELEASE_MASK
			 // | GDK_SCROLL_MASK
			 // | GDK_KEY_PRESS_MASK
                         // | GDK_KEY_RELEASE_MASK
                         | GDK_POINTER_MOTION_MASK
                         | GDK_POINTER_MOTION_HINT_MASK
                         | GDK_VISIBILITY_NOTIFY_MASK);

  gtk_widget_show(p->da);
#endif

#if 0
  gtk_signal_connect (GTK_OBJECT (p->da), "expose_event",
                      (GtkSignalFunc) expose_event, (gpointer)p);

  gtk_signal_connect (GTK_OBJECT(p->da),"configure_event",
                      (GtkSignalFunc) configure_event, (gpointer)p);

  gtk_signal_connect (GTK_OBJECT (p->da), "motion_notify_event",
                      (GtkSignalFunc) viewer_motion_notify_event, (gpointer)p);

  gtk_signal_connect (GTK_OBJECT (p->da), "button_press_event",
                      (GtkSignalFunc) viewer_button_press_event, (gpointer)p);

  gtk_signal_connect (GTK_OBJECT (p->da), "button_release_event",
                      (GtkSignalFunc) viewer_button_release_event, (gpointer)p);
#endif

#if 0
  gtk_signal_connect (GTK_OBJECT (p->da), "scroll_event",
                      (GtkSignalFunc) viewer_scroll_event, (gpointer)p);
#endif

  gtk_widget_show(box);
  gtk_container_add(GTK_CONTAINER (p->topwindow), box);
  gtk_widget_show(p->topwindow);

#if 0
  p->image_gc = gdk_gc_new (p->da->window);
#endif

  // gdk_gc_set_exposures (p->image_gc,1);

  gtk_main();

  return 1;
}
