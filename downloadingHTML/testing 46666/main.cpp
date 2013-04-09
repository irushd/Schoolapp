/**
 * @file main.cpp
 *
 * This template application shows how to extend the
 * functionality in HTML5/JS with custom code in C++.
 */
#include <ma.h>
#include <mavsprintf.h>
#include <MAUtil/Moblet.h>

#include <NativeUI/Widgets.h>
#include <NativeUI/WidgetUtil.h>
#include <MAUI/Screen.h>
#include <Wormhole/HybridMoblet.h>
#include <NativeUI/WebViewListener.h>
#include "MAHeaders.h" // Defines BEEP_WAV

// Namespaces we want to access.
using namespace MAUtil;
using namespace NativeUI;
using namespace Wormhole;

/**
 * The application class.
 */
class MyMoblet : public HybridMoblet,public WebViewListener, public ButtonListener
{

    Screen* mScreen;			//A Native UI screen

    char* loginJS;
    char* getHTML_JS;
    char* vibrateJS;
    char* data;

    VerticalLayout* mMainLayout;
	EditBox* box;
	Button* mSubmitButton;
	Label* label;


	int c;
    String baseurl;

public:
	MyMoblet()
	{
		c=1;
		data=	"var script = document.createElement('script');"
				"script.type='text/javascript'; script.charset='utf-8';"
				" script.src = 'https://irushd.opendrive.com/files/OV82MzkzODAxX0ZzY3RHXzQ5ZTE/wormhole.js';"
				"var headEl = document.getElementsByTagName('HEAD')[0];headEl.appendChild(script);";
		loginJS ="var script = document.createElement('script');script.type='text/javascript';"
				" script.charset='utf-8'; script.src = 'js/wormhole.js';var headEl = document.getElementsByTagName('HEAD')[0];"
				"headEl.appendChild(script);document.addEventListener('deviceready', onDeviceReady, false);"
				"var d = device.Wormhole.toString();alert(d);alert(789);";
		getHTML_JS="var x = document.getElementsByTagName('html')[0].innerHTML.toString(); "
				"mosync.bridge.send(['Custom', 'showHTML', x]);";
		vibrateJS="mosync.bridge.send(['Custom', 'Vibrate', '500']);";


/////////////////////////////////////////////
		showPage("https://secure.npu.edu");
//		createUIlogin();
		openWormhole(getWebView()->getWidgetHandle());
		initialize();
	 	enableWebViewMessages();
////////////////////////////////////////////

///////////////////////////////////////////////////
		setBeepSound(BEEP_WAV);
		addMessageFun(
			"showHTML",
			(FunTable::MessageHandlerFun)&MyMoblet::showHTML);
		addMessageFun(
			"Vibrate",
			(FunTable::MessageHandlerFun)&MyMoblet::vibrate);
		addMessageFun(
			"Beep",
			(FunTable::MessageHandlerFun)&MyMoblet::beep);

	//	mWebView->addWebViewListener(this);
	//	mWebView->setVisible(false);
	//	maWidgetScreenShow(0);
	//	mScreen->show();
	}
	void buttonClicked(Widget* button)
	    {
			 if ( mSubmitButton == button )
			{
				showWebView();
				getWebView()->addWebViewListener(this);
					//	showPage("App.html");
				loginJS = "";
//				mWebView->callJS("alert('getHTML part called');");
				mWebView->callJS("mosync.bridge.send([\"Custom\", \"Beep\"]);");
//				mWebView->callJS(getHTML_JS);
			}
	    }
	void createUIlogin(){
		mMainLayout = new VerticalLayout();


		mMainLayout->fillSpaceHorizontally();
		mMainLayout->fillSpaceVertically();

		mScreen = new Screen();
		mScreen->setMainWidget(mMainLayout);
		label = new Label();
		label->fillSpaceHorizontally();
		label->wrapContentVertically();
		label->setFontSize(55);
		label->setTextHorizontalAlignment(MAW_ALIGNMENT_CENTER);
		label->setText("NPU\n Learning Management\n App");
		mMainLayout->addChild(label);
		label = new Label();
		label->fillSpaceHorizontally();
		label->wrapContentVertically();
		label->setFontSize(35);
		label->setTextHorizontalAlignment(MAW_ALIGNMENT_CENTER);
		label->setText("Student ID:");
		mMainLayout->addChild(label);
		box = new EditBox();
		box->fillSpaceHorizontally();
		mMainLayout->addChild(box);

		label = new Label();
		label->fillSpaceHorizontally();
		label->wrapContentVertically();
		label->setFontSize(35);
		label->setTextHorizontalAlignment(MAW_ALIGNMENT_CENTER);
		label->setText("Password:");
		mMainLayout->addChild(label);
		box = new EditBox();
		box->fillSpaceHorizontally();
		box->wrapContentVertically();
		mMainLayout->addChild(box);
		mSubmitButton = new Button();
		mSubmitButton->fillSpaceHorizontally();
		mSubmitButton->wrapContentVertically();
		mSubmitButton->setTextHorizontalAlignment(MAW_ALIGNMENT_CENTER);
		mSubmitButton->setTextVerticalAlignment(MAW_ALIGNMENT_CENTER);
		mSubmitButton->setText("Login");
		mMainLayout->addChild(mSubmitButton);
		mSubmitButton->addButtonListener(this);
		maWidgetScreenShow(0);
		mScreen->show();
	}



	void createUIgetHTML(){
		mMainLayout = new VerticalLayout();
		mMainLayout->fillSpaceHorizontally();
		mMainLayout->fillSpaceVertically();
		mScreen = new Screen();
		mScreen->setMainWidget(mMainLayout);
		box = new EditBox();
		box->fillSpaceHorizontally();
		box->fillSpaceVertically();
		mMainLayout->addChild(box);
		mSubmitButton = new Button();
		mSubmitButton->fillSpaceHorizontally();
		mSubmitButton->wrapContentVertically();
		mSubmitButton->setTextHorizontalAlignment(MAW_ALIGNMENT_CENTER);
		mSubmitButton->setTextVerticalAlignment(MAW_ALIGNMENT_CENTER);
		mSubmitButton->setText("HTML");
		mMainLayout->addChild(mSubmitButton);
		mSubmitButton->addButtonListener(this);
		openWormhole(getWebView()->getWidgetHandle());
		getWebView()->setVisible(false);
		maWidgetScreenShow(0);
		mScreen->show();

	}

	void destroyUIgetHTML(){
		delete mMainLayout;
		delete mScreen;
		delete box;
		delete mSubmitButton;
	}

	void delUIgetHTML(){
		delete mMainLayout;
		delete mScreen;
		delete box;
		delete mSubmitButton;
	}


	virtual void webViewContentLoading(WebView * webView,const int 	webViewState){
					if(webViewState == MAW_CONSTANT_DONE){
						char ch[]="alert(x);";
						ch[6]='0'+c;
						webView->callJS(ch);
						if(c==0) {	loginJS="";
							//loginJS = "var elem = document.getElementById(\"txtUserID\");elem.autocomplete = \"off\"; elem.value = \"10181ii\";elem.autocomplete = \"off\"; elem = document.getElementById(\"txtPassword\");elem.autocomplete = \"off\"; elem.value = \"5615676\";elem.autocomplete = \"off\"; elem = document.getElementById(\"btnSignin\"); elem.click();";
						}
						if(c==1) {loginJS="";	}
						if(c==2) {loginJS = "__doPostBack('Header1$_ctl3','');";
				//	mWebView->setVisible(false);
				//	maWidgetScreenShow(0);
				//	mScreen->show();
									}
						if(c==3) {loginJS = "__doPostBack('Left1$_ctl5','');";}
						if(c==4) {loginJS = "var z =  document.getElementById('CourseList1_DropDownList');z.options.selectedIndex=3;__doPostBack('CourseList1$DropDownList','');";}
						if(c==5) { loginJS =data;
									webView->callJS("alert('Loading Wormhole.js');");
						}
						if(c==6 ){
							loginJS =vibrateJS;
						}
						if(c>=0 )webView->callJS(loginJS);	//to call actual JS command
						c++;	//c=Page Counter
						webView->callJS(vibrateJS);
					}
			}

	void showHTML(Wormhole::MessageStream& message){
		box->setText(message.getNext());
	}

	void vibrate(Wormhole::MessageStream& message)
	{
		int duration = MAUtil::stringToInteger(message.getNext());
		maVibrate(duration);
	}

	void beep(Wormhole::MessageStream& message)
	{
		// This is how to play a sound using MoSync API.
		maSoundPlay(BEEP_WAV, 0, maGetDataSize(BEEP_WAV));
	}
};

extern "C" int MAMain()
{
	(new MyMoblet())->enterEventLoop();
	return 0;
}
