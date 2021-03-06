#ifndef MGUI_H
#define MGUI_H

struct NVGcontext;

int mgInit();
void mgTerminate();

enum MUImouseButton {
	MG_MOUSE_PRESSED	= 1 << 0,
	MG_MOUSE_RELEASED	= 1 << 1,
};

enum MUIoverflow {
	MG_FIT,
	MG_HIDDEN,
	MG_SCROLL,
	MG_VISIBLE,
};

enum MUIdir {
	MG_ROW,
	MG_COL,
};

enum MUIalign {
	MG_START,
	MG_END,
	MG_CENTER,
	MG_JUSTIFY,
};

#define MG_AUTO_SIZE 0xffff

enum MGargTypes {
	MG_NONE = 0,			// 0
	MG_WIDTH_ARG,			
	MG_HEIGHT_ARG,
	MG_PROPWIDTH_ARG,
	MG_PROPHEIGHT_ARG,
	MG_SPACING_ARG,
	MG_PADDINGX_ARG,
	MG_PADDINGY_ARG,
	MG_GROW_ARG,
	MG_ALIGN_ARG,
	MG_PACK_ARG,			// 10
	MG_OVERFLOW_ARG,
	MG_FONTSIZE_ARG,
	MG_LINEHEIGHT_ARG,
	MG_TEXTALIGN_ARG,
	MG_LOGIC_ARG,
	MG_STYLE_ARG,
	MG_CONTENTCOLOR_ARG,
	MG_FILLCOLOR_ARG,
	MG_BORDERCOLOR_ARG,
	MG_BORDERSIZE_ARG,
	MG_CORNERRADIUS_ARG,	// 20
	MG_TAG_ARG,
	MG_ANCHOR_ARG,
	MG_PROPX_ARG,
	MG_PROPY_ARG,
	MG_X_ARG,
	MG_Y_ARG,
};

enum MGlogicType {
	MG_CLICK = 1,
	MG_DRAG = 2,
	MG_TYPE = 3,
};


#define mgOverflow(v)			(mgPackOpt(MG_OVERFLOW_ARG, (v)))
#define mgAlign(v)				(mgPackOpt(MG_ALIGN_ARG, (v)))
#define mgPack(v)				(mgPackOpt(MG_PACK_ARG, (v)))
#define mgGrow(v)				(mgPackOpt(MG_GROW_ARG, (v)))

#define mgWidth(v)				(mgPackOptf(MG_WIDTH_ARG, (v)))
#define mgHeight(v)				(mgPackOptf(MG_HEIGHT_ARG, (v)))
#define mgPropWidth(v)			(mgPackOptf(MG_PROPWIDTH_ARG, (v)))
#define mgPropHeight(v)			(mgPackOptf(MG_PROPHEIGHT_ARG, (v)))
#define mgPosition(a,b,x,y)		(mgPackOpt2(MG_ANCHOR_ARG, (a), (b))), (mgPackOptf(MG_X_ARG, (x))), (mgPackOptf(MG_Y_ARG, (y)))
#define mgPropPosition(a,b,x,y)	(mgPackOpt2(MG_ANCHOR_ARG, (a), (b))), (mgPackOptf(MG_PROPX_ARG, (x))), (mgPackOptf(MG_PROPY_ARG, (y)))

#define mgPaddingX(v)			(mgPackOpt(MG_PADDINGX_ARG, (v)))
#define mgPaddingY(v)			(mgPackOpt(MG_PADDINGY_ARG, (v)))
#define mgPadding(x,y)			(mgPackOpt(MG_PADDINGX_ARG, (x))), (mgPackOpt(MG_PADDINGY_ARG, (y)))
#define mgSpacing(v)			(mgPackOpt(MG_SPACING_ARG, (v)))

#define mgFontSize(v)			(mgPackOpt(MG_FONTSIZE_ARG, (v)))
#define mgTextAlign(v)			(mgPackOpt(MG_TEXTALIGN_ARG, (v)))
#define mgLineHeight(v)			(mgPackOptf(MG_LINEHEIGHT_ARG, (v)))

#define mgLogic(v)				(mgPackOpt(MG_LOGIC_ARG, (v)))

#define mgContentColor(r,g,b,a)	(mgPackOpt(MG_CONTENTCOLOR_ARG, mgRGBA((r),(g),(b),(a))))
#define mgFillColor(r,g,b,a)	(mgPackOpt(MG_FILLCOLOR_ARG, mgRGBA((r),(g),(b),(a))))
#define mgBorderColor(r,g,b,a)	(mgPackOpt(MG_BORDERCOLOR_ARG, mgRGBA((r),(g),(b),(a))))
#define mgBorderSize(v)			(mgPackOpt(MG_BORDERSIZE_ARG, (v)))
#define mgCornerRadius(v)		(mgPackOpt(MG_CORNERRADIUS_ARG, (v)))
#define mgTag(v)				(mgPackOptStr(MG_TAG_ARG, (v)))

struct MGopt {
	unsigned char type;
	unsigned char units;
	union {
		float fval;
		int ival;
		char* sval;
	};
	struct MGopt* next;
};

struct MGstyle {
	unsigned int set;

	float width;
	float height;
	float x;
	float y;

	unsigned int contentColor;
	unsigned int fillColor;
	unsigned int borderColor;

	unsigned char cornerRadius;
	unsigned char borderSize;

	unsigned char spacing;
	unsigned char paddingx;
	unsigned char paddingy;

	unsigned char grow;
	unsigned char align;
	unsigned char pack;
	unsigned char overflow;

	unsigned char fontSize;
	unsigned char textAlign;
	float lineHeight;

	unsigned char logic;
	unsigned char anchor;
};


#define mgOpts(...) mgOpts_(0, ##__VA_ARGS__, NULL)
struct MGopt* mgOpts_(unsigned int dummy, ...);
struct MGopt* mgPackOpt(unsigned char arg, int v);
struct MGopt* mgPackOptf(unsigned char arg, float v);
struct MGopt* mgPackOpt2(unsigned char arg, int x, int y);
struct MGopt* mgPackOptStr(unsigned char arg, const char* str);
unsigned int mgRGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
unsigned int mgCreateStyle(const char* selector, struct MGopt* normal, struct MGopt* hover, struct MGopt* active, struct MGopt* focus);

struct MGrect {
	float x, y, width, height;
};

struct MGhit {
	float mx, my;
	float deltamx, deltamy;
	float localmx, localmy;
	int mods;
	unsigned int code;
	int clickCount;

	struct MGrect rect;
	struct MGrect view;
	struct MGstyle style;
};

enum MGwidgetType {
	MG_BOX,
	MG_PANEL,
	MG_POPUP,
	MG_PARAGRAPH,
	MG_TEXT,
	MG_ICON,
	MG_INPUT,
	MG_CANVAS,
};

enum MGwidgetState {
	MG_NORMAL = 0,
	MG_HOVER = 1<<0,
	MG_ACTIVE = 1<<1,
	MG_FOCUS = 1<<2,
};

enum MGwidgetEvent {
	MG_FOCUSED,
	MG_BLURRED,
	MG_CLICKED,
	MG_PRESSED,
	MG_RELEASED,
	MG_DRAGGED,
	MG_ENTERED,
	MG_EXITED,
	MG_KEYPRESSED,
	MG_KEYRELEASED,
	MG_CHARTYPED,
};

struct MGwidget;

typedef void (*MGcanvasRenderFun)(void* uptr, struct MGwidget* w, struct NVGcontext* vg, const float* view);
typedef void (*MGcanvasLogicFun)(void* uptr, struct MGwidget* w, int event, struct MGhit* hit);

struct MGwidget {
	unsigned int id;
	float x, y, width, height;
	float cwidth, cheight;
	
	struct MGstyle style;

	unsigned char dir;
	unsigned char type;
	unsigned char state;
	unsigned char stop;

	unsigned char active;
	unsigned char bubble;

	union {
		struct {
			struct MGicon* icon;
		} icon;
		char* text;
	};

	MGcanvasLogicFun logic;
	MGcanvasRenderFun render;
	void* uptr;
	int uptrsize;

	const char* tag;

	struct MGwidget* next;
	struct MGwidget* parent;
	struct MGwidget* children;
};

#define MG_MAX_INPUTKEYS 32
struct MGkeyPress {
	int type, code, mods;
};
struct MGinputState
{
	float mx, my;
	int mbut;
	struct MGkeyPress keys[MG_MAX_INPUTKEYS];
	int nkeys;	
};

void mgFrameBegin(struct NVGcontext* vg, int width, int height, struct MGinputState* input, float dt);
void mgFrameEnd();

int mgCreateIcon(const char* name, const char* filename);

unsigned int mgPanelBegin(int dir, float x, float y, int zidx, struct MGopt* opts);
unsigned int mgPanelEnd();

unsigned int mgBoxBegin(int dir, struct MGopt* opts);
unsigned int mgBoxEnd();
unsigned int mgBox(struct MGopt* opts);

unsigned int mgText(const char* text, struct MGopt* opts);
unsigned int mgParagraph(const char* text, struct MGopt* opts);
unsigned int mgIcon(const char* name, struct MGopt* opts);
unsigned int mgInput(char* text, int maxtext, struct MGopt* opts);

unsigned int mgCanvas(float width, float height, MGcanvasLogicFun logic, MGcanvasRenderFun render, struct MGopt* opts);

// Derivative
unsigned int mgNumber(float* value, struct MGopt* opts);
unsigned int mgSelect(int* value, const char** choices, int nchoises, struct MGopt* opts);
unsigned int mgLabel(const char* text, struct MGopt* opts);
unsigned int mgNumber3(float* x, float* y, float* z, const char* units, struct MGopt* opts);
unsigned int mgColor(float* r, float* g, float* b, float* a, struct MGopt* opts);
unsigned int mgCheckBox(const char* text, int* value, struct MGopt* opts);
unsigned int mgButton(const char* text, struct MGopt* opts);
unsigned int mgIconButton(const char* icon, const char* text, struct MGopt* opts);
unsigned int mgItem(const char* text, struct MGopt* opts);
unsigned int mgSlider(float* value, float vmin, float vmax, struct MGopt* opts);
unsigned int mgProgress(float progress, struct MGopt* opts);
unsigned int mgScrollBar(float* offset, float contentSize, float viewSize, struct MGopt* opts);

unsigned int mgPopupBegin(unsigned int target, int trigger, int dir, struct MGopt* opts);
unsigned int mgPopupEnd();
void mgShowPopup(unsigned int id, int show);

unsigned int mgTooltip(unsigned int target, const char* message, struct MGopt* opts);

int mgClicked(unsigned int id);
int mgPressed(unsigned int id);
int mgDragged(unsigned int id);
int mgReleased(unsigned int id);
int mgBlurred(unsigned int id);
int mgFocused(unsigned int id);
int mgExited(unsigned int id);
int mgEntered(unsigned int id);
int mgChanged(unsigned int id);

int mgIsActive(unsigned int id);
int mgIsHover(unsigned int id);
int mgIsFocus(unsigned int id);

void mgFocus(unsigned int id);
void mgFocusNext(unsigned int id);
void mgFocusPrev(unsigned int id);
void mgBlur(unsigned int id);


#endif // MGUI_H
