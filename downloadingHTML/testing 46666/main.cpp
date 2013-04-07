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

	int c;
    String baseurl;

public:
	MyMoblet()
	{
		c=0;
		data="var script = document.createElement('script');script.type='text/javascript'; script.charset='utf-8'; script.src = 'https://irushd.opendrive.com/files/OV82MzkzODAxX0ZzY3RHXzQ5ZTE/wormhole.js';var headEl = document.getElementsByTagName('HEAD')[0];headEl.appendChild(script);";
		loginJS ="alert(123);var script = document.createElement('script');script.type='text/javascript'; script.charset='utf-8'; script.src = 'js/wormhole.js';var headEl = document.getElementsByTagName('HEAD')[0];headEl.appendChild(script);document.addEventListener('deviceready', onDeviceReady, false); alert(456);var d = device.Wormhole.toString();alert(d);alert(789);";
		getHTML_JS="var x = document.getElementsByTagName('html')[0].innerHTML.toString(); mosync.bridge.send(['Custom', 'showHTML', x]);";
		vibrateJS="mosync.bridge.send(['Custom', 'Vibrate', '500']);";

/////////////////////////////////////////////
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

////////////////////////////////////////////
		showWebView();
	//	showPage("App.html");
		showPage("https://secure.npu.edu");
		initialize();
	 	openWormhole(getWebView()->getWidgetHandle());
	 	enableWebViewMessages();

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

		getWebView()->addWebViewListener(this);
	//	mWebView->addWebViewListener(this);
	//	mWebView->setVisible(false);
	//	maWidgetScreenShow(0);
	//	mScreen->show();
	}
	void buttonClicked(Widget* button)
	    {
			 if ( mSubmitButton == button )
			{
				mWebView->callJS("alert('getHTML part called');");
				mWebView->callJS("mosync.bridge.send([\"Custom\", \"Beep\"]);");
				mWebView->callJS(getHTML_JS);
			}
	    }

	virtual void webViewContentLoading(WebView * webView,const int 	webViewState){
					if(webViewState == MAW_CONSTANT_DONE){
						char ch[]="alert(x);";
						ch[6]='0'+c;
						webView->callJS(ch);

						if(c==0) {	//loginJS = "var elem = document.getElementById(\"txtUserID\");elem.autocomplete = \"off\"; elem.value = \"10181ii\";elem.autocomplete = \"off\"; elem = document.getElementById(\"txtPassword\");elem.autocomplete = \"off\"; elem.value = \"5615676\";elem.autocomplete = \"off\"; elem = document.getElementById(\"btnSignin\"); elem.click();";
				//		openWormhole(webView->getWidgetHandle());
						loginJS=data;
						//loginJS=vibrateJS;
							webView->setVisible(false);
							maWidgetScreenShow(0);
							mScreen->show();
						}
						if(c==1) { loginJS=vibrateJS;	}
						if(c==2) {loginJS = "__doPostBack('Header1$_ctl3','');";
				//	mWebView->setVisible(false);
				//	maWidgetScreenShow(0);
				//		mScreen->show();
									}
						if(c==3) {loginJS = "__doPostBack('Left1$_ctl5','');";}
						if(c==4) {loginJS = "var z =  document.getElementById('CourseList1_DropDownList');z.options.selectedIndex=3;__doPostBack('CourseList1$DropDownList','');";}
						if(c==5) { loginJS =data;
						webView->callJS("alert('Loading Wormhole.js');");
						openWormhole(webView->getWidgetHandle());
						webView->callJS(data);
						webView->callJS(vibrateJS);
						//testing
						//	data;	//	openWormhole(mWebView->getWidgetHandle());
						/*// Register functions to handle custom messages sent
							// from JavaScript.
							addMessageFun(
								"showHTML",
								(FunTable::MessageHandlerFun)&MyMoblet::showHTML);
							addMessageFun(
								"Vibrate",
								(FunTable::MessageHandlerFun)&MyMoblet::vibrate);
							addMessageFun(
								"Beep",
								(FunTable::MessageHandlerFun)&MyMoblet::beep);

	*/
						}
						if(c==6 ){
							loginJS =vibrateJS; //data;
						}
						if(c>=0 )webView->callJS(loginJS);	//to call actual JS command
						c++;	//c=Page Counter
						webView->callJS(vibrateJS);
					}
			}


/*
	virtual void webViewContentLoading(WebView * webView,const int 	webViewState){
			if(webViewState == MAW_CONSTANT_DONE){
				++c;
				//	if(c>=2)
				//	{
					webView->callJS("alert('WebPage+Wormhole.js Loaded and Beep called');");
					webView->callJS("mosync.bridge.send([\"Custom\", \"Beep\"]);");
				//	}
			//	else {
			//		webView->callJS(data);
			//	}
	}
	}
*/
	void showHTML(Wormhole::MessageStream& message){
		mWebView->setVisible(false);
		maWidgetScreenShow(0);
		box->setText(message.getNext());
		mScreen->show();
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
