@charset "UTF-8";

/* --- xenforo.css --- */

/*
 * YUI reset-fonts.css
 *
Copyright (c) 2009, Yahoo! Inc. All rights reserved.
Code licensed under the BSD License:
http://developer.yahoo.net/yui/license.txt
version: 2.7.0
*/
html{color:#000;background:#FFF;}body,div,dl,dt,dd,ul,ol,li,h1,h2,h3,h4,h5,h6,pre,code,form,fieldset,legend,input,button,textarea,p,blockquote,th,td{margin:0;padding:0;}table{border-collapse:collapse;border-spacing:0;}fieldset,img{border:0;}address,caption,cite,code,dfn,em,strong,th,var,optgroup{font-style:inherit;font-weight:inherit;}del,ins{text-decoration:none;}li{list-style:none;}caption,th{text-align:left;}h1,h2,h3,h4,h5,h6{font-size:100%;font-weight:normal;}q:before,q:after{content:'';}abbr,acronym{border:0;font-variant:normal;text-decoration:none}sup{vertical-align:baseline;}sub{vertical-align:baseline;}legend{color:#000;}input,button,textarea,select,optgroup,option{font-family:inherit;font-size:inherit;font-style:inherit;font-weight:inherit;}input,button,textarea,select{*font-size:100%;}body{font:13px/1.231 arial,helvetica,clean,sans-serif;*font-size:small;*font:x-small;}select,input,button,textarea,button{font:99% arial,helvetica,clean,sans-serif;}table{font-size:inherit;font:100%;}pre,code,kbd,samp,tt{font-family:monospace;*font-size:108%;line-height:100%;}

/*
 * Firefox broken image placeholder support.
 *
http://lab.gmtplusone.com/image-placeholder/
*/ 
img:-moz-broken, img:-moz-user-disabled { -moz-force-broken-image-icon: 1; }
img:-moz-broken:not([width]), img:-moz-user-disabled:not([width]) { width: 50px; }
img:-moz-broken:not([height]), img:-moz-user-disabled:not([height]) { height: 50px; }

/*
 * XenForo Core CSS
 *
 */

html
{
	background-color: #1B1F20;

	overflow-y: scroll !important;
}

body
{
	-webkit-text-size-adjust: 100%;
	-moz-text-size-adjust: 100%;
	-ms-text-size-adjust: 100%;
	text-size-adjust: 100%;

	font-family: Verdana,"Segoe UI",Arial,Meiryo,sans-serif;
color: #141414;
word-wrap: break-word;
line-height: 1.5;

}

/* counteract the word-wrap setting in 'body' */
pre, textarea
{
	word-wrap: normal;
}

[dir=auto] { text-align: left; }

a:link,
a:visited
{
	color: #176093;
text-decoration: none;

}

	a[href]:hover
	{
		color: rgb(173, 20, 87);

	}
	
	a:hover
	{
		_text-decoration: underline;
	}
	
	a.noOutline
	{
		outline: 0 none;
	}
	
	.emCtrl {border-radius:5px;}
	.messageContent .messageText a {text-decoration:underline;}
	
		.emCtrl:hover,
		.emCtrl:focus,
		.ugc a:hover,
		.ugc a:focus
		{
			/*position: relative;
			top: -1px;*/
			text-decoration: none;
			box-shadow: 5px 5px 7px #CCCCCC;
			outline: 0 none;
		}
		
			.emCtrl:active,
			.ugc a:active
			{
				position: relative;
				top: 1px;
				box-shadow: 2px 2px 7px #CCCCCC;
				outline: 0 none;
			}

	.ugc a:link,
	.ugc a:visited
	{
		padding: 0 3px;
margin: 0 -3px;
border-radius: 5px;

	}
	
		.ugc a:hover,
		.ugc a:focus
		{
			
		}
		
img.mceSmilie,
img.mceSmilieSprite
{
	vertical-align: text-bottom;
	margin: 0 1px;
}
		
/** title bar **/

.titleBar
{
	margin-bottom: 10px;
}

/* clearfix */ .titleBar { zoom: 1; } .titleBar:after { content: '.'; display: block; height: 0; clear: both; visibility: hidden; }

.titleBar h1
{
	font-size: 24px;
font-family: Roboto,"Segoe UI",Arial,sans-serif;
color: #FFF;
background-color: #333;
padding: 3px 10px;
margin: 0;
background-image: linear-gradient(#3E3E3E,#000000);
/*10px*/

}

	.titleBar h1 em
	{
		color: #6CB2E4;
	}
		
	.titleBar h1 .Popup
	{
		float: left;
	}

#pageDescription
{
	color: #FFCC00;
margin-top: 2px;
display: none;

}

.topCtrl
{
	float: right;
}
	
	.topCtrl h2
	{
		font-size: 12pt;
	}
		
/** images **/

img
{
	-ms-interpolation-mode: bicubic;
}

a.avatar 
{ 
	*cursor: pointer; /* IE7 refuses to do this */ 
} 

.avatar img,
.avatar .img,
.avatarCropper
{
	padding: 2px;

}

.avatar.plainImage img,
.avatar.plainImage .img
{
	border: none;
	border-radius: 0;
	padding: 0;
	background-position: left top;
}

	.avatar .img
	{
		display: block;
		background-repeat: no-repeat;
		background-position: 2px 2px;
		text-indent: 1000px;
		overflow: hidden;
		white-space: nowrap;
		word-wrap: normal;
	}

	.avatar .img.s { width: 48px;  height: 48px;  }
	.avatar .img.m { width: 96px;  height: 96px;  }
	.avatar .img.l { width: 192px; height: 192px; }

.avatarCropper
{
	width: 192px;
	height: 192px;
	direction: ltr;
}

.avatarCropper a,
.avatarCropper span,
.avatarCropper label
{
	overflow: hidden;
	position: relative;
	display: block;
	width: 192px;
	height: 192px;
}

.avatarCropper img
{
	padding: 0;
	border: none;
	border-radius: 0;

	position: relative;
	display: block;
}

.avatarScaler img
{
	max-width: 192px;
	_width: 192px;
}

/* ***************************** */

body .dimmed, body a.dimmed, body .dimmed a { color: #646464; }
body .muted, body a.muted, body .muted a { color: #969696; }
body .faint, body a.faint, body .faint a { color: #C8C8C8; }

.highlight { font-weight: bold; }

.concealed,
.concealed a,
.cloaked,
.cloaked a
{
	text-decoration: inherit !important;
	color: inherit !important;
	*clear:expression( style.color = parentNode.currentStyle.color, style.clear = "none", 0);
}

a.concealed:hover,
.concealed a:hover
{
	text-decoration: underline !important;
}

/* ***************************** */

.xenTooltip
{
	font-size: 11px;
color: #FFFFFF;
background: url(rgba.php?r=0&g=0&b=0&a=153); background: rgba(0,0,0,0.6); _filter: progid:DXImageTransform.Microsoft.gradient(startColorstr=#99000000,endColorstr=#99000000);
padding: 5px 10px;
border-radius: 5px;
display: none;
z-index: 15000;
cursor: default;

}

.xenTooltip a,
.xenTooltip a:hover
{
	color: #FFFFFF;
	text-decoration: underline;
}

	.xenTooltip .arrow
	{
		border-top:  6px solid rgb(0,0,0); border-top:  6px solid rgba(0,0,0, 0.6); _border-top:  6px solid rgb(0,0,0);
border-right: 6px solid transparent;
border-bottom: 1px none black;
border-left: 6px solid transparent;
position: absolute;
bottom: -6px;
line-height: 0px;
width: 0px;
height: 0px;

		left: 9px;
		
		/* Hide from IE6 */
		_display: none;
	}

	.xenTooltip.flipped .arrow
	{
		left: auto;
		right: 9px;
	}

.xenTooltip.statusTip
{
	/* Generated by XenForo.StatusTooltip JavaScript */
	padding: 5px 10px;
line-height: 17px;
width: 250px;
height: auto;

}

	.xenTooltip.statusTip .arrow
	{
		border: 6px solid transparent;
border-right-color:  rgb(0,0,0); border-right-color:  rgba(0,0,0, 0.6); _border-right-color:  rgb(0,0,0);
border-left: 1px none black;
top: 6px;
left: -6px;
bottom: auto;
right: auto;

	}
			
.xenTooltip.iconTip { margin-left: -6px; }
.xenTooltip.iconTip.flipped { margin-left: 7px; }

/* ***************************** */

#PreviewTooltip
{
	display: none;
}

.xenPreviewTooltip
{
	border: 10px solid #333;
border-radius: 10px;
position: relative;
box-shadow: 0px 12px 25px rgba(0,0,0,0.5);
width: 400px;

	
	display: none;	
	z-index: 15000;
	cursor: default;
	
	border-color:  rgb(51, 51, 51); border-color:  rgba(51, 51, 51, 0.5); _border-color:  rgb(51, 51, 51);
}

	.xenPreviewTooltip .arrow
	{
		border-top:  15px solid rgb(3,42,70); border-top:  15px solid rgba(3,42,70, 0.25); _border-top:  15px solid rgb(3,42,70);
border-right: 15px solid transparent;
border-bottom: 1px none black;
border-left: 15px solid transparent;
position: absolute;
bottom: -15px;
left: 22px;

		
		_display: none;
	}
	
		.xenPreviewTooltip .arrow span
		{
			border-top: 15px solid #FCFCFF;
border-right: 15px solid transparent;
border-bottom: 1px none black;
border-left: 15px solid transparent;
position: absolute;
top: -17px;
left: -15px;

		}

	.xenPreviewTooltip .section,
	.xenPreviewTooltip .sectionMain,
	.xenPreviewTooltip .primaryContent,
	.xenPreviewTooltip .secondaryContent
	{
		margin: 0;
	}
	
		.xenPreviewTooltip .previewContent
		{
			overflow: hidden; zoom: 1;
			min-height: 1em;
		}

/* ***************************** */

.importantMessage
{
	margin: 10px 0;
	color: #303030;
	background-color: #D6E0EA;
	text-align: center;
	padding: 5px;
	border-radius: 5px;
	border: solid 1px #FFDD44;
}

.importantMessage a
{
	font-weight: bold;
	color: #303030;
}

/* ***************************** */

.section
{
	background-color: #FCFCFF;
margin: 10px auto;

}

.sectionMain
{
	margin: 0;

}

.heading,
.xenForm .formHeader
{
	font-size: 14px;
color: #F0F7FC;
background-color: #303030;
padding: 11px 10px;
margin: 0 auto;
background-image: linear-gradient(#3E3E3E,#000000);

}

	.heading a { color: #F0F7FC; }

.subHeading
{
	font-size: 14px;
color: #FFF;
background-color: #303030;
padding: 11px 10px;
margin: 0 auto;
background-image: linear-gradient(#3E3E3E,#000000);
/* hardcoded colors - white text on dark bg */

}

	.subHeading a { color: #FFF; }

.textHeading,
.xenForm .sectionHeader
{
	font-weight: bold;
color: #141414;
padding-bottom: 2px;
margin: 10px auto 5px;
border-bottom: 1px solid #D7EDFC;

}

.xenForm .sectionHeader,
.xenForm .formHeader
{
	margin: 10px 0;
}

.primaryContent > .textHeading:first-child,
.secondaryContent > .textHeading:first-child
{
	margin-top: 0;
}

.larger.textHeading,
.xenForm .sectionHeader
{
	color: #CFE3F1;
	font-size: 11pt;
	margin-bottom: 6px;
}

.larger.textHeading a,
.xenForm .sectionHeader a
{
	color: #CFE3F1;
}
.xenForm .sectionHeader,
.xenForm .sectionHeader a {color:#6CB2E4;}


.primaryContent
{
	background-color: #FCFCFF;
padding: 10px;
border-bottom: 1px solid #D7EDFC;

}

/*
	.primaryContent a
	{
		color: #176093;

	}
*/

.secondaryContent
{
	color: #141414;
background-color: #F0F7FC;
padding: 10px;
border-bottom: 1px solid #D7EDFC;
background-image: linear-gradient(#F0F7FC,#FCFCFF);

}

	.secondaryContent a
	{
		color: #176093;

	}

.sectionFooter
{
	overflow: hidden; zoom: 1;
	font-size: 11px;
color: #646464;
background-color: #FFFFFF;
padding: 4px 10px;
border-bottom: 1px solid #CFE3F1;
line-height: 16px;

}

	.sectionFooter a { color: #646464; }

	.sectionFooter .left
	{
		float: left;
	}

	.sectionFooter .right
	{
		float: right;
	}

/* used for section footers with central buttons, esp. in report viewing */

.actionList
{
	text-align: center;
}

/* left-right aligned options */

.opposedOptions
{
	overflow: hidden; zoom: 1;
}
	
	.opposedOptions .left
	{
		float: left;
	}
	
	.opposedOptions .right
	{
		float: right;
	}

.columns
{
	overflow: hidden; zoom: 1;
}

	.columns .columnContainer
	{
		float: left;
	}
	
		.columns .columnContainer .column
		{
			margin-left: 3px;
		}
		
		.columns .columnContainer:first-child .column
		{
			margin-left: 0;
		}

.c50_50 .c1,
.c50_50 .c2 { width: 49.99%; }

.c70_30 .c1 { width: 70%; }
.c70_30 .c2 { width: 29.99%; }

.c60_40 .c1 { width: 60%; }
.c60_40 .c2 { width: 39.99%; }

.c40_30_30 .c1 { width: 40%; }
.c40_30_30 .c2,
.c40_30_30 .c3 { width: 29.99%; }

.c50_25_25 .c1 { width: 50%; }
.c50_25_25 .c2,
.c50_25_25 .c3 { width: 25%; }

/* ***************************** */
/* Basic Tabs */

.tabs
{
	font-size: 11px;
background-color: #FCFCFF;
padding: 0 10px;
border-bottom: 1px solid #C8C8C8;
word-wrap: normal;
min-height: 23px;
_height: 23px;

	
	display: table;
	width: 100%;
	*width: auto;
	box-sizing: border-box;
}

.tabs li
{
	float: left;
}

.tabs li a,
.tabs.noLinks li
{
	color: #141414;
text-decoration: none;
background-color: #E5EFF9;
padding: 0 8px;
margin-right: -1px;
margin-bottom: -1px;
border: 1px solid #969696;
border-top-left-radius: 5px;
border-top-right-radius: 5px;
display: inline-block;
line-height: 22px;
cursor: pointer;
outline: 0 none;
white-space: nowrap;
word-wrap: normal;
height: 22px;

}

.tabs li:hover a,
.tabs.noLinks li:hover
{
	color: #141414;
text-decoration: none;
background-color: #C8C8C8;
		
}

.tabs li.active a,
.tabs.noLinks li.active
{
	background-color: #FCFCFF;
padding-bottom: 1px;
border-bottom: 1px none black;

}

/* Tabs inside forms */

.xenForm .tabs,
.xenFormTabs
{
	padding: 5px 30px 0;
}


@media (max-width:480px)
{
	.Responsive .tabs li
	{
		float: none;
	}

	.Responsive .tabs li a,
	.Responsive .tabs.noLinks li
	{
		display: block;
	}
	
	.Responsive .tabs
	{
		display: flex;
		display: -webkit-flex;
		flex-wrap: wrap;
		-webkit-flex-wrap: wrap;
	}
	
	.Responsive .tabs li
	{
		flex-grow: 1;
		-webkit-flex-grow: 1;
		text-align: center;
	}
	
	.Responsive .xenForm .tabs,
	.Responsive .xenFormTabs
	{
		padding-left: 10px;
		padding-right: 10px;
	}
}


/* ***************************** */
/* Popup Menus */

.Popup
{
	position: relative;
}

	.Popup.inline
	{
		display: inline;
	}
	
/** Popup menu trigger **/

.Popup .arrowWidget
{
	/* circle-arrow-down */
	background: transparent url('styles/default/xenforo/xenforo-ui-sprite.png') no-repeat -32px 0;
margin-top: -2px;
margin-left: 2px;
display: inline-block;
*margin-top: 0;
vertical-align: middle;
width: 13px;
height: 14px;

}

.PopupOpen .arrowWidget
{
	/* circle-arrow-up */
	background-position: -16px 0;

}

.Popup .PopupControl,
.Popup.PopupContainerControl
{
	display: inline-block;
	cursor: pointer;
}

	.Popup .PopupControl:hover,
	.Popup.PopupContainerControl:hover
	{
		text-decoration: none;

	}

	.Popup .PopupControl:focus,
	.Popup .PopupControl:active,
	.Popup.PopupContainerControl:focus,
	.Popup.PopupContainerControl:active
	{
		outline: 0;
	}
	
	.Popup .PopupControl.PopupOpen,
	.Popup.PopupContainerControl.PopupOpen
	{
		border-top-left-radius: 3px;
border-top-right-radius: 3px;
border-bottom-right-radius: 0px;
border-bottom-left-radius: 0px;
/*text-shadow: 1px 1px 2px white;*/

	}
	
	.Popup .PopupControl.BottomControl.PopupOpen,
	.Popup.PopupContainerControl.BottomControl.PopupOpen
	{
		border-top-left-radius: 0px;
		border-top-right-radius: 0px;
		border-bottom-left-radius: 3px;
		border-bottom-right-radius: 3px;
	}
		
		.Popup .PopupControl.PopupOpen:hover,
		.Popup.PopupContainerControl.PopupOpen:hover
		{
			text-decoration: none;
		}
		
/** Menu body **/

.Menu
{
	/*background-color: #FFFFFF;*/
	
	font-size: 13px;
border: 1px solid #444;
border-top: 5px solid #444;
overflow: hidden;
box-shadow: 0 5px 5px rgba(0,0,0,0.5);

	
	min-width: 200px;
	*width: 200px;
	
	/* makes menus actually work... */
	position: absolute;
	z-index: 7500;
	display: none;
}

/* allow menus to operate when JS is disabled */
.Popup:hover .Menu
{
	display: block;
}

.Popup:hover .Menu.JsOnly
{
	display: none;
}

.Menu.BottomControl
{
	border-top-width: 1px;
	border-bottom-width: 3px;
	box-shadow: 0px 0px 0px transparent;
}

	.Menu > li > a,
	.Menu .menuRow
	{
		display: block;
	}
	
.Menu.inOverlay
{
	z-index: 10000;
}
		
/* Menu header */

.Menu .menuHeader
{
	overflow: hidden; zoom: 1;
}

.Menu .menuHeader h3
{
	font-size: 18px;

}

.Menu .menuHeader .muted
{
	font-size: 14px;

}

/* Standard menu sections */

.Menu .primaryContent
{
	background-color: rgba(252, 252, 255, 0.96);
}

.Menu .secondaryContent
{
	background-color: rgba(240, 247, 252, 0.96);
}

.Menu .sectionFooter
{
	background-color: rgba(255, 255, 255, 0.9);
}

/* Links lists */

.Menu .blockLinksList
{	
	max-height: 400px;
	overflow: auto;
}

/* form popups */

.formPopup
{
	width: 250px;
	background-color: #FCFCFF;
}

	.formPopup form,
	.formPopup .ctrlUnit
	{
		margin: 5px auto;
	}
	
		.formPopup .ctrlUnit
		{
		}
		
	.formPopup .textCtrl,
	.formPopup .button
	{
		width: 232px;
	}
		
	.formPopup .ctrlUnit > dt label
	{
		display: block;
		margin-bottom: 2px;
	}
		
	.formPopup .submitUnit dd
	{
		text-align: center;
	}
	
		.formPopup .ctrlUnit > dd .explain
		{
			margin: 2px 0 0;
		}
	
	.formPopup .primaryControls
	{
		zoom: 1;
		white-space: nowrap;
		word-wrap: normal;
		padding: 0 5px;
	}
	
		.formPopup .primaryControls input.textCtrl
		{
			margin-bottom: 0;
		}
	
	.formPopup .secondaryControls
	{
		padding: 0 5px;
	}
	
		.formPopup .controlsWrapper
		{
			background-color:#D7EDFC;
			background-image:linear-gradient(#CFE3F1,#D7EDFC);
			border-radius: 5px;
			padding: 5px;
			margin: 5px 0;
			font-size: 11px;
		}

			.formPopup .controlsWrapper .textCtrl
			{
				width: 222px;
			}
	
	.formPopup .advSearchLink
	{
		display: block;
		text-align: center;
		padding: 5px;
		font-size: 11px;
		border-radius: 5px;
		border: 1px solid #D7EDFC;
		background-color:#F0F7FC;
		background-image:linear-gradient(#D7EDFC,#F0F7FC);
	}
	
		.formPopup .advSearchLink:hover
		{
			background-color: #D7EDFC;
			text-decoration: none;
		}

/* All overlays must have this */
.xenOverlay
{
	display: none;
	z-index: 10000;
	width: 90%;
	box-sizing: border-box;
	max-width: 690px; /*calc: 90=overlay padding+borders*/
}

	.xenOverlay .overlayScroll
	{
		max-height: 400px;
		overflow: auto;
	}
	
	.xenOverlay .overlayScroll.ltr
	{
		direction: ltr;
	}
	
	.xenOverlay .overlayScroll .sortable-placeholder
	{
		background-color: #CFE3F1;
	}
	
	.xenOverlay .overlayContain
	{
		overflow-x: auto;
	}
	
	.xenOverlay .overlayContain.ltr
	{
		direction: ltr;
	}

.overlayOnly /* needs a bit more specificity over regular buttons */
{
	display: none !important;
}

	.xenOverlay .overlayOnly
	{
		display: block !important;
	}
	
	.xenOverlay input.overlayOnly,
	.xenOverlay button.overlayOnly,
	.xenOverlay a.overlayOnly
	{
		display: inline !important;
	}
	
	.xenOverlay a.close 
	{
		background-image: url('styles/default/xenforo/overlay/close.png');
position: absolute;
right: 4px;
top: 4px;
cursor: pointer;
width: 35px;
height: 35px;

	}
	
.xenOverlay .nonOverlayOnly
{
	display: none !important;
}

/* Generic form overlays */

.xenOverlay .formOverlay
{
	color: #EEE;
background: url(rgba.php?r=0&g=0&b=0&a=191); background: rgba(0,0,0, 0.75); _filter: progid:DXImageTransform.Microsoft.gradient(startColorstr=#BF000000,endColorstr=#BF000000);
padding: 15px 25px;
border:  20px solid rgb(0,0,0); border:  20px solid rgba(0,0,0, 0.25); _border:  20px solid rgb(0,0,0);
border-radius: 20px;
box-shadow: 0px 25px 50px rgba(0,0,0, 0.5);
_zoom: 1;

	margin: 0;
}

	.Touch .xenOverlay .formOverlay
	{
		background: rgb(0, 0, 0);
		box-shadow: none;
	}

	.xenOverlay .formOverlay a.muted,
	.xenOverlay .formOverlay .muted a
	{
		color: #969696;
	}

	.xenOverlay .formOverlay .heading
	{
		font-weight: bold;
font-size: 16px;
padding: 5px 10px;
margin-bottom: 10px;
border: 1px solid #2B485C;
border-radius: 5px;
/*color: #F0F7FC;*/
/*background-color: #176093;*/

	}

	.xenOverlay .formOverlay .subHeading
	{
		font-weight: bold;
font-size: 11px;
background-color: #2B485C;
padding: 5px 10px;
margin-bottom: 10px;
border: 1px solid #176093;
border-radius: 3px;
/*color: #F0F7FC;*/

	}
	
	.xenOverlay .formOverlay .textHeading
	{
		color: #F0F7FC;

	}
	
	.xenOverlay .formOverlay > p
	{
		padding-left: 10px;
		padding-right: 10px;
	}

	.xenOverlay .formOverlay .textCtrl
	{
		color: #CCC;
background: #000 none;
border-color: #CFE3F1;
/*#F0F7FC*/

	}

	.xenOverlay .formOverlay .textCtrl option
	{
		background: #000 none;
	}

	.xenOverlay .formOverlay .textCtrl:focus,
	.xenOverlay .formOverlay .textCtrl.Focus
	{
		background: #000 none;

	}

	.xenOverlay .formOverlay .textCtrl:focus option
	{
		background: #000 none;
	}


	.xenOverlay .formOverlay .textCtrl.disabled
	{
		background: url(rgba.php?r=0&g=0&b=0&a=63); background: rgba(0,0,0, 0.25); _filter: progid:DXImageTransform.Microsoft.gradient(startColorstr=#3F000000,endColorstr=#3F000000);

	}

	.xenOverlay .formOverlay .textCtrl.disabled option
	{
		background: url(rgba.php?r=0&g=0&b=0&a=63); background: rgba(0,0,0, 0.25); _filter: progid:DXImageTransform.Microsoft.gradient(startColorstr=#3F000000,endColorstr=#3F000000);
	}

	.xenOverlay .formOverlay .textCtrl.prompt
	{
		color: rgb(160,160,160);

	}

	.xenOverlay .formOverlay .ctrlUnit > dt dfn,
	.xenOverlay .formOverlay .ctrlUnit > dd li .hint,
	.xenOverlay .formOverlay .ctrlUnit > dd .explain
	{
		color: #BBB;

	}

	.xenOverlay .formOverlay a
	{
		color: #FFF;

	}

		.xenOverlay .formOverlay a.button
		{
			
		}

	.xenOverlay .formOverlay .avatar img,
	.xenOverlay .formOverlay .avatar .img,
	.xenOverlay .formOverlay .avatarCropper
	{
		background-color: transparent;
	}
	
	/* tabs in form overlay */
	
	.xenOverlay .formOverlay .tabs /* the actual tabs */
	{
		background: transparent none;
border-color: #CFE3F1;

	}

		.xenOverlay .formOverlay .tabs a
		{
			background: transparent none;
border-color: #CFE3F1;

		}
		
			.xenOverlay .formOverlay .tabs a:hover
			{
				background: url(rgba.php?r=255&g=255&b=255&a=63); background: rgba(255,255,255, 0.25); _filter: progid:DXImageTransform.Microsoft.gradient(startColorstr=#3FFFFFFF,endColorstr=#3FFFFFFF);

			}
			
			.xenOverlay .formOverlay .tabs .active a
			{
				background: #000 none;

			}
			
	.xenOverlay .formOverlay .tabPanel /* panels switched with the tab controls */
	{
		background: transparent url('styles/default/xenforo/color-picker/panel.png') repeat-x top;
border: 1px solid #CFE3F1;

	}


/* Generic overlays */

.xenOverlay .section,
.xenOverlay .sectionMain
{
	padding: 0px;
border:  20px solid rgb(51,51,51); border:  20px solid rgba(51,51,51, 0.5); _border:  20px solid rgb(51,51,51);
border-radius: 20px;
box-shadow: 0px 25px 50px rgba(0,0,0, 0.5);

}

	.Touch .xenOverlay .section,
	.Touch .xenOverlay .sectionMain
	{
		border-color: rgb(51, 51, 51);
		box-shadow: none;
	}

.xenOverlay > .section,
.xenOverlay > .sectionMain
{
	background: none;
	margin: 0;
}

	.xenOverlay .section .heading,
	.xenOverlay .sectionMain .heading
	{
		border-radius: 0;
		margin-bottom: 0;
	}

	.xenOverlay .section .subHeading,
	.xenOverlay .sectionMain .subHeading
	{
		margin-top: 0;
	}

	.xenOverlay .section .sectionFooter,
	.xenOverlay .sectionMain .sectionFooter
	{
		overflow: hidden; zoom: 1;
	}
		
		.xenOverlay .sectionFooter .buttonContainer
		{
			line-height: 31px;
		}
	
		.xenOverlay .sectionFooter .button,
		.xenOverlay .sectionFooter .buttonContainer
		{
			min-width: 75px;
			*min-width: 0;
			float: right;
			margin-left: 5px;
		}
		
			.xenOverlay .sectionFooter .buttonContainer .button
			{
				float: none;
				margin-left: 0;
			}

/* The AJAX progress indicator overlay */

#AjaxProgress.xenOverlay
{
	width: 100%;
	max-width: none;
	overflow: hidden; zoom: 1;
}

	#AjaxProgress.xenOverlay .content
	{
		background: rgb(0, 0, 0) url('styles/default/xenforo/widgets/ajaxload.info_FFFFFF_facebook.gif') no-repeat center center; background: rgba(0,0,0, 0.5) url('styles/default/xenforo/widgets/ajaxload.info_FFFFFF_facebook.gif') no-repeat center center;
border-bottom-left-radius: 10px;
float: right;
width: 85px;
height: 30px;

	}
	
		.Touch #AjaxProgress.xenOverlay .content
		{
			background-color: rgb(0, 0, 0);
		}

/* Timed message for redirects */

.xenOverlay.timedMessage
{
	color: black;
background: transparent url('styles/default/xenforo/overlay/timed-message.png') repeat-x;
border-bottom: 1px solid black;
max-width: none;
width: 100%;

}

	.xenOverlay.timedMessage .content
	{
		font-size: 18pt;
padding: 30px;
text-align: center;

	}
	
/* Growl-style message */

#StackAlerts
{
	position: fixed;
	bottom: 70px;
	left: 35px;
	z-index: 9999; /* in front of the expose mask */
}

	#StackAlerts .stackAlert
	{
		position: relative;
		width: 270px;
		border: 1px solid #6CB2E4;
		border-radius: 5px;
		box-shadow: 2px 2px 5px 0 rgba(0,0,0, 0.4);
		margin-top: 5px;
	}

		#StackAlerts .stackAlertContent
		{
			padding: 10px;
			padding-right: 30px;
			border-radius: 4px;
			border: solid 2px #D7EDFC;
			background: url(rgba.php?r=240&g=247&b=252&a=229); background: rgba(240, 247, 252, 0.9); _filter: progid:DXImageTransform.Microsoft.gradient(startColorstr=#E5F0F7FC,endColorstr=#E5F0F7FC);
			font-size: 11px;
			font-weight: bold;
		}
	
/* Inline Editor */

.xenOverlay .section .messageContainer
{
	padding: 0;
}

.xenOverlay .section .messageContainer .mceLayout
{
	border: none;	
}

.xenOverlay .section .messageContainer tr.mceFirst td.mceFirst
{
	border-top: none;
}

.xenOverlay .section .messageContainer tr.mceLast td.mceLast,
.xenOverlay .section .messageContaner tr.mceLast td.mceIframeContainer
{
	border-bottom: none;
}

.xenOverlay .section .textCtrl.MessageEditor,
.xenOverlay .section .mceLayout,
.xenOverlay .section .bbCodeEditorContainer textarea
{
	width: 100% !important;
	min-height: 260px;
	_height: 260px;
	box-sizing: border-box;
}


@media (max-width:610px)
{
	.Responsive .xenOverlay
	{
		width: 100%;
	}
	
	.Responsive .xenOverlay .formOverlay,
	.Responsive .xenOverlay .section,
	.Responsive .xenOverlay .sectionMain
	{
		border-radius: 10px;
		border-width: 10px;
	}
	
	.Responsive .xenOverlay a.close 
	{
		top: 0;
		right: 0;
		width: 28px;
		height: 28px;
		background-size: 100% 100%;
	}
}


.alerts .alertGroup
{
	margin-bottom: 20px;
}

.alerts .primaryContent
{
	overflow: hidden; zoom: 1;
	padding: 5px;
}

.alerts .avatar
{
	float: left;
}

.alerts .avatar img
{
	width: 32px;
	height: 32px;
}

.alerts .alertText
{
	margin-left: 32px;
	padding: 0 5px;
}

.alerts h3
{
	display: inline;
}

.alerts h3 .subject
{
	font-weight: bold;
}

.alerts .timeRow
{
	font-size: 11px;
	margin-top: 5px;
}
	
	.alerts .newIcon,
	.alertsPopup .newIcon
	{
		display: inline-block;
		vertical-align: baseline;
		margin-left: 2px;
		width: 11px;
		height: 11px;
		background: url('styles/default/xenforo/xenforo-ui-sprite.png') no-repeat -144px -40px;
	}

/** Data tables **/

.dataTableWrapper
{
	overflow-x: auto;
	overflow-y: visible;
}

table.dataTable
{
	width: 100%;
	_width: 99.5%;
	margin: 10px 0;
}

.dataTable caption
{
	font-size: 14px;
color: #F0F7FC;
background-color: #303030;
padding: 11px 10px;
margin: 0 auto;
background-image: linear-gradient(#3E3E3E,#000000);

}

.dataTable tr.dataRow td
{
	border-bottom: 1px solid #D7EDFC;
	padding: 5px 10px;
	word-wrap: break-word;
}

.dataTable tr.dataRow td.secondary
{
	background-color:#F0F7FC;
	background-image:linear-gradient(#D7EDFC,#F0F7FC);
}

.dataTable tr.dataRow th
{
	background-color:#E5EFF9;
	background-image:linear-gradient(#CFE3F1,#E5EFF9);
	border-bottom: 1px solid #FFDD44;
	border-top: 1px solid #E5EFF9;
	color: #303030;
	font-size: 11px;
	padding: 5px 10px;
}

	.dataTable tr.dataRow th a
	{
		color: inherit;
		text-decoration: underline;
	}

.dataTable .dataRow .dataOptions
{
	text-align: right;
	white-space: nowrap;
	word-wrap: normal;
	padding: 0;
}

.dataTable .dataRow .important,
.dataTable .dataRow.important
{
	font-weight: bold;
}

.dataTable .dataRow .dataOptions a.secondaryContent
{
	display: inline-block;
	border-left: 1px solid #D7EDFC;
	border-bottom: none;
	padding: 7px 10px 6px;
	font-size: 11px;
}

	.dataTable .dataRow .dataOptions a.secondaryContent:hover
	{
		background-color: #D7EDFC;
		text-decoration: none;
	}

	.dataTable .dataRow .delete
	{
		padding: 0px;
		width: 26px;
		border-left: 1px solid #D7EDFC;
		background-color: #F0F7FC;
	}	
				
		.dataTable .dataRow .delete a
		{
			display: block;
			background: transparent url('styles/default/xenforo/permissions/deny.png') no-repeat center center;
			cursor: pointer;
		
			padding: 5px;
			width: 16px;
			height: 16px;
			
			overflow: hidden;
			white-space: nowrap;
			text-indent: -1000px;
		}

.memberListItem
{
	overflow: hidden;
zoom: 1;

}

	.memberListItem .avatar,
	.memberListItem .icon
	{
		float: left;

	}
	
	/* ----------------------- */
	
	.memberListItem .extra
	{
		font-size: 11px;
float: right;

	}

		.memberListItem .extra .DateTime
		{
			display: block;
		}

		.memberListItem .extra .bigNumber
		{
			font-size: 250%;
			color: #969696;
		}
	
	.memberListItem .member
	{
		margin-left: 65px;

	}
	
	/* ----------------------- */
		
		.memberListItem h3.username
		{
			font-weight: bold;
font-size: 13pt;
margin-bottom: 3px;

		}
			
		.memberListItem .username.guest
		{
			font-style: italic;
font-weight: normal;

		}
	
	/* ----------------------- */
		
		.memberListItem .userInfo
		{
			font-size: 11px;
margin-bottom: 3px;

		}
		
			.memberListItem .userBlurb
			{
			}
		
				.memberListItem .userBlurb .userTitle
				{
					font-weight: bold;

				}

			.memberListItem .userStats dt,
			.memberListItem .userStats dd
			{
				white-space: nowrap;
			}
				
	
	/* ----------------------- */
		
		.memberListItem .member .contentInfo
		{
			margin-top: 5px;

		}
	
	/* ----------------------- */
	
	
/* extended member list items have a fixed 200px right column */

.memberListItem.extended .extra
{
	width: 200px;
}

.memberListItem.extended .member
{
	margin-right: 210px;
}

/* Styling for hover-dismiss controls */

.DismissParent .DismissCtrl
{
	position: absolute;
	top: 12px;
	right: 5px;
	
	display: block;
	background: transparent url('styles/default/xenforo/xenforo-ui-sprite.png') no-repeat -80px 0;
	color: white;
	width: 15px;
	height: 15px;
	line-height: 15px;
	text-align: center;
	
	opacity: .4;
	-webkit-transition: opacity 0.3s ease-in-out;
	-moz-transition: opacity 0.3s ease-in-out;
	transition: opacity 0.3s ease-in-out;
	
	font-size: 10px;
	
	overflow: hidden;
	white-space: nowrap;
	text-indent: 20000em;
	
	cursor: pointer;
}

	.DismissParent:hover .DismissCtrl,
	.Touch .DismissParent .DismissCtrl
	{
		opacity: 1;
	}
	
		.DismissParent:hover .DismissCtrl:hover
		{
			background-position: -96px 0;
		}
		
			.DismissParent:hover .DismissCtrl:active
			{
				background-position: -112px 0;
			}
			
.DismissParent.notice_-1 .DismissCtrl
{
	display: none;
}

/* ***************************** */
/* un-reset, mostly from YUI */

.baseHtml h1
	{ font-size:138.5%; } 
.baseHtml h2
	{ font-size:123.1%; }
.baseHtml h3
	{ font-size:108%; } 
.baseHtml h1, .baseHtml h2, .baseHtml h3
	{  margin:1em 0; } 
.baseHtml h1, .baseHtml h2, .baseHtml h3, .baseHtml h4, .baseHtml h5, .baseHtml h6, .baseHtml strong
	{ font-weight:bold; } 
.baseHtml abbr, .baseHtml acronym
	{ border-bottom:1px dotted #000; cursor:help; }  
.baseHtml em
	{  font-style:italic; } 
.baseHtml blockquote, .baseHtml ul, .baseHtml ol, .baseHtml dl
	{ margin:1em; } 
.baseHtml ol, .baseHtml ul, .baseHtml dl
	{ margin-left:3em; margin-right:0; } 
.baseHtml ul ul, .baseHtml ul ol, .baseHtml ul dl, .baseHtml ol ul, .baseHtml ol ol, .baseHtml ol dl, .baseHtml dl ul, .baseHtml dl ol, .baseHtml dl dl
	{ margin-top:0; margin-bottom:0; }
.baseHtml ol li
	{ list-style: decimal outside; } 
.baseHtml ul li
	{ list-style: disc outside; } 
.baseHtml ol ul li, .baseHtml ul ul li
	{ list-style-type: circle; }
.baseHtml ol ol ul li, .baseHtml ol ul ul li, .baseHtml ul ol ul li, .baseHtml ul ul ul li
	{ list-style-type: square; }
.baseHtml ul ol li, .baseHtml ul ol ol li, .baseHtml ol ul ol li
	{ list-style: decimal outside; }
.baseHtml dl dd
	{ margin-left:1em; } 
.baseHtml th, .baseHtml td
	{ border:1px solid #000; padding:.5em; } 
.baseHtml th
	{ font-weight:bold; text-align:center; } 
.baseHtml caption
	{ margin-bottom:.5em; text-align:center; } 
.baseHtml p, .baseHtml pre, .baseHtml fieldset, .baseHtml table
	{ margin-bottom:1em; }

.PageNav
{
	font-size: 13px;
color: #D7EDFC;
margin:0!important; /* otherwise it goes -0.5em for some reason */
overflow: hidden;
zoom: 1;
word-wrap: normal;
min-width: 150px;
white-space: nowrap;

	
	margin-bottom: -.5em;
}

	.PageNav .hidden
	{
		display: none;
	}
	
	.PageNav .pageNavHeader,
	.PageNav a,
	.PageNav .scrollable
	{
		display: block;
		float: left;
		margin-right: 5px;
		margin-bottom: .5em;
	}
	
	.PageNav .pageNavHeader
	{
		padding: 1px 0;
	}

	.PageNav a
	{		
		color: #444444;
text-decoration: none;
background-color: #D6E0EA;
text-align: center;

		
		
		width: 25px;
	}
		
		.PageNav a[rel=start]
		{
			width: 25px !important;
		}

		.PageNav a.text
		{
			width: auto !important;
			padding: 0 4px;
		}
			
		.PageNav a.currentPage
		{
			color: #2B485C;
background-color: #F0F7FC;
position: relative;

		}

		a.PageNavPrev,
		a.PageNavNext
		{
			cursor: pointer;

			
			width: 25px !important;
		}
		
		.PageNav a:hover,
		.PageNav a:focus
		{
			color: #444444;
text-decoration: none;
background-color: #E5EFF9;

		}
		
	.PageNav a.distinct
	{
		margin-left: 5px;
	}
			
	.PageNav .scrollable
	{
		position: relative;
		overflow: hidden;
		width: 145px; /* width of 5 page numbers plus their margin & border */
		height: 18px; /* only needs to be approximate */
	}
	
		.PageNav .scrollable .items
		{
			display: block;
			width: 20000em; /* contains scrolling items, should be huge */
			position: absolute;
		}
		
/** Edge cases - large numbers of digits **/

.PageNav .gt999 
{
	font-size: 9px;
	letter-spacing: -0.05em; 
}

.PageNav.pn5 a { width: 29px; } .PageNav.pn5 .scrollable { width: 165px; }
.PageNav.pn6 a { width: 33px; } .PageNav.pn6 .scrollable { width: 185px; }
.PageNav.pn7 a { width: 37px; } .PageNav.pn7 .scrollable { width: 205px; }


@media (max-width:610px)
{
	.Responsive .PageNav .pageNavHeader
	{
		display: none;
	}
}

@media (max-width:480px)
{
	.Responsive .PageNav .unreadLink
	{
		display: none;
	}
}


/* ***************************** */
/* DL Name-Value Pairs */

.pairs dt,
.pairsInline dt,
.pairsRows dt,
.pairsColumns dt,
.pairsJustified dt
{
	color: #969696;
}

.pairsRows,
.pairsColumns,
.pairsJustified
{
	line-height: 1.5;
}

.pairsInline dl,
.pairsInline dt,
.pairsInline dd
{
	display: inline;
}

.pairsRows dt,
.pairsRows dd
{
	display: inline-block;
	vertical-align: top;

	*display: inline;
	*margin-right: 1ex;
	*zoom: 1;
}

dl.pairsColumns,
dl.pairsJustified,
.pairsColumns dl,
.pairsJustified dl
{
	overflow: hidden; zoom: 1;
}

.pairsColumns dt,
.pairsColumns dd
{
	float: left;
	width: 48%;
}

.pairsJustified dt
{
	float: left;
	max-width: 100%;
	margin-right: 5px;
}
.pairsJustified dd
{
	float: right;
	text-align: right;
	max-width: 100%
}


/* ***************************** */
/* Lists that put all elements on a single line */

.listInline ul,
.listInline ol,
.listInline li,
.listInline dl,
.listInline dt,
.listInline dd
{
	display: inline;
}

/* intended for use with .listInline, produces 'a, b, c, d' / 'a * b * c * d' lists */

.commaImplode li:after,
.commaElements > *:after
{
	content: ', ';
}

.commaImplode li:last-child:after,
.commaElements > *:last-child:after
{
	content: '';
}

.bulletImplode li:before
{
	content: '\2022\a0';
}

.bulletImplode li:first-child:before
{
	content: '';
}

/* Three column list display */

.threeColumnList
{
	overflow: hidden; zoom: 1;
}

.threeColumnList li
{
	float: left;
	width: 32%;
	margin: 2px 1% 2px 0;
}

.twoColumnList
{
	overflow: hidden; zoom: 1;
}

.twoColumnList li
{
	float: left;
	width: 48%;
	margin: 2px 1% 2px 0;
}

/* ***************************** */
/* Preview tooltips (threads etc.) */

.previewTooltip
{
}
		
	.previewTooltip .avatar
	{
		float: left;
	}
	
	.previewTooltip .text
	{
		margin-left: 64px;
	}
	
		.previewTooltip blockquote
		{
			font-size: 16px;
font-family: Roboto,"Segoe UI",Arial,sans-serif;
line-height: 1.4;

			
			font-size: 10pt;
			max-height: 150px;
			overflow: hidden;
		}
	
		.previewTooltip .posterDate
		{
			font-size: 11px;
			padding-top: 5px;
			border-top: 1px solid #D7EDFC;
			margin-top: 5px;
		}

/* ***************************** */
/* List of block links */

.blockLinksList
{
	font-size: 11px;
padding: 2px;

}
		
	.blockLinksList a,
	.blockLinksList label
	{
		color: #176093;
padding: 5px 10px;
border-radius: 5px;
display: block;
outline: 0 none;

	}
	
		.blockLinksList a:hover,
		.blockLinksList a:focus,
		.blockLinksList li.kbSelect a,
		.blockLinksList label:hover,
		.blockLinksList label:focus,
		.blockLinksList li.kbSelect label
		{
			text-decoration: none;
background-color: #D7EDFC;

		}
		
		.blockLinksList a:active,
		.blockLinksList li.kbSelect a:active,
		.blockLinksList a.selected,
		.blockLinksList li.kbSelect a.selected,
		.blockLinksList label:active,
		.blockLinksList li.kbSelect label:active,
		.blockLinksList label.selected,
		.blockLinksList li.kbSelect label.selected
		{
			color: #FFFFFF;
background-color: #65A5D1;

		}
		
		.blockLinksList a.selected,
		.blockLinksList li.kbSelect a.selected,
		.blockLinksList label.selected,
		.blockLinksList li.kbSelect label.selected
		{
			font-weight: bold;
display: block;

		}
		
		.blockLinksList span.depthPad
		{
			display: block;
		}

.blockLinksList .itemCount
{
	font-weight: bold;
font-size: 9px;
color: white;
background-color: #e03030;
padding: 0 2px;
border-radius: 2px;
position: absolute;
right: 2px;
top: -12px;
line-height: 16px;
min-width: 12px;
_width: 12px;
text-align: center;
text-shadow: none;
white-space: nowrap;
word-wrap: normal;
box-shadow: 2px 2px 5px rgba(0,0,0, 0.25);
height: 16px;


	float: right;
	position: relative;
	right: 0;
	top: -1px;
}

	.blockLinksList .itemCount.Zero
	{
		display: none;
	}
	
.bubbleLinksList
{
	overflow: hidden;
}

.bubbleLinksList a
{
	float: left;
	padding: 2px 4px;
	margin-right: 2px;
	border-radius: 3px;
	text-decoration: none;
}
	
	.bubbleLinksList a:hover,
	.bubbleLinksList a:active
	{
		text-decoration: none;
background-color: #D7EDFC;

	}
	
	.bubbleLinksList a.active
	{
		color: #FFFFFF;
background-color: #65A5D1;

		font-weight: bold;
display: block;

	}

/* ***************************** */
/* Normally-indented nested lists */

.indentList ul,
.indentList ol
{
	margin-left: 2em;
}

/* ***************************** */
/* AJAX progress image */

.InProgress
{
	background: transparent url('styles/default/xenforo/widgets/ajaxload.info_B4B4DC_facebook.gif') no-repeat right center;
}

/* ***************************** */
/* Hidden inline upload iframe */

.hiddenIframe
{
	display: block;
	width: 500px;
	height: 300px;
}

/* ***************************** */
/* Exception display */

.traceHtml { font-size:11px; font-family:calibri, verdana, arial, sans-serif; }
.traceHtml .function { color:rgb(180,80,80); font-weight:normal; }
.traceHtml .file { font-weight:normal; }
.traceHtml .shade { color:rgb(128,128,128); }
.traceHtml .link { font-weight:bold; }

/* ***************************** */
/* Indenting for options */

._depth0 { padding-left:  0em; }
._depth1 { padding-left:  2em; }
._depth2 { padding-left:  4em; }
._depth3 { padding-left:  6em; }
._depth4 { padding-left:  8em; }
._depth5 { padding-left: 10em; }
._depth6 { padding-left: 12em; }
._depth7 { padding-left: 14em; }
._depth8 { padding-left: 16em; }
._depth9 { padding-left: 18em; }

.xenOverlay .errorOverlay
{
	color: white;
	padding: 25px;
	border-radius: 20px;	
	border:  20px solid rgb(0,0,0); border:  20px solid rgba(0,0,0, 0.25); _border:  20px solid rgb(0,0,0);
	
	background: url(rgba.php?r=0&g=0&b=0&a=191); background: rgba(0,0,0, 0.75); _filter: progid:DXImageTransform.Microsoft.gradient(startColorstr=#BF000000,endColorstr=#BF000000);
}

	.xenOverlay .errorOverlay .heading
	{
		padding: 5px 10px;
		font-weight: bold;
		font-size: 12pt;
		background: rgb(180,0,0);
		color: white;
		margin-bottom: 10px;
		border-radius: 5px;
		border: 1px solid rgb(100,0,0);
	}

	.xenOverlay .errorOverlay li
	{
		line-height: 2;
	}
	
	.xenOverlay .errorOverlay .exceptionMessage
	{
		color: #969696;
	}

/*** inline errors ***/

.formValidationInlineError
{
	display: none;
	position: absolute;
	z-index: 5000;
	background-color: white;
	border: 1px solid rgb(180,0,0);
	color: rgb(180,0,0);
	box-shadow: 2px 2px 10px #999;
	border-radius: 3px;
	padding: 2px 5px;
	font-size: 11px;
	width: 175px;
	min-height: 2.5em;
	_height: 2.5em;
	word-wrap: break-word;
}

	.formValidationInlineError.inlineError
	{
		position: static;
		width: auto;
		min-height: 0;
	}

/** Block errors **/

.errorPanel
{
	margin: 10px 0 20px;
	color: rgb(180,0,0);
	background: rgb(255, 235, 235);
	border-radius: 5px;
	border: 1px solid rgb(180,0,0);
}

	.errorPanel .errorHeading
	{
		margin: .75em;
		font-weight: bold;
		font-size: 12pt;
	}
	
	.errorPanel .errors
	{
		margin: .75em 2em;
		display: block;
		line-height: 1.5;
	}


@media (max-width:800px)
{
	.Responsive .formValidationInlineError
	{
		position: static;
		width: auto;
		min-height: auto;
	}
}


/* Undo some nasties */

input[type=search]
{
	-webkit-appearance: textfield;
	box-sizing: content-box;
}

/* ignored content hiding */

.ignored { display: none !important; }

/* Misc */

.floatLeft { float: left; }
.floatRight { float: right; }

.horizontalContain { overflow-x: auto; }

.ltr { direction: ltr; }

/* Square-cropped thumbs */

.SquareThumb
{
	position: relative;
	display: block;
	overflow: hidden;
	padding: 0;
	direction: ltr;
	
	/* individual instances can override this size */
	width: 48px;
	height: 48px;
}

.SquareThumb img
{
	position: relative;
	display: block;
}

/* Basic, common, non-templated BB codes */

.bbCodeImage
{
	max-width: 100%;
}

.bbCodeImageFullSize
{
	position: absolute;
	z-index: 50000;
	background-color: #FCFCFF;
}

.bbCodeStrike
{
	text-decoration: line-through;
}

img.mceSmilie,
img.mceSmilieSprite
{
	vertical-align: text-bottom;
	margin: 0 1px;
}

/* smilie sprite classes */

img.mceSmilieSprite.mceSmilie49
{
	width: 28px; height: 28px; background: url('/data/attachments/smilies/default_3.png') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie50
{
	width: 28px; height: 28px; background: url('/data/attachments/smilies/default_1.png') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie53
{
	width: 28px; height: 28px; background: url('/data/attachments/smilies/default_5.png') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie51
{
	width: 28px; height: 28px; background: url('/data/attachments/smilies/default_4b.png') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie48
{
	width: 28px; height: 28px; background: url('/data/attachments/smilies/default_2.png') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie52
{
	width: 28px; height: 28px; background: url('/data/attachments/smilies/default_4.png') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie56
{
	width: 28px; height: 28px; background: url('/data/attachments/smilies/alexus-3.png') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie54
{
	width: 28px; height: 28px; background: url('/data/attachments/smilies/alexus-1.png') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie69
{
	width: 28px; height: 28px; background: url('/data/attachments/smilies/alexus-6.png') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie58
{
	width: 28px; height: 28px; background: url('/data/attachments/smilies/alexus-5.png') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie55
{
	width: 28px; height: 28px; background: url('/data/attachments/smilies/alexus-2.png') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie57
{
	width: 28px; height: 28px; background: url('/data/attachments/smilies/alexus-4.png') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie92
{
	width: 28px; height: 28px; background: url('/data/attachments/smilies/elmer-3.png') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie90
{
	width: 28px; height: 28px; background: url('/data/attachments/smilies/elmer-1.png') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie95
{
	width: 28px; height: 28px; background: url('/data/attachments/smilies/elmer-6.png') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie94
{
	width: 28px; height: 28px; background: url('/data/attachments/smilies/elmer-5.png') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie91
{
	width: 28px; height: 28px; background: url('/data/attachments/smilies/elmer-2.png') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie93
{
	width: 28px; height: 28px; background: url('/data/attachments/smilies/elmer-4.png') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie61
{
	width: 28px; height: 28px; background: url('/data/attachments/smilies/eric-3.png') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie59
{
	width: 28px; height: 28px; background: url('/data/attachments/smilies/eric-1.png') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie70
{
	width: 28px; height: 28px; background: url('/data/attachments/smilies/eric-6.png') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie63
{
	width: 28px; height: 28px; background: url('/data/attachments/smilies/eric-5.png') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie60
{
	width: 28px; height: 28px; background: url('/data/attachments/smilies/eric-2.png') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie62
{
	width: 28px; height: 28px; background: url('/data/attachments/smilies/eric-4.png') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie66
{
	width: 28px; height: 28px; background: url('/data/attachments/smilies/harold-3.png') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie64
{
	width: 28px; height: 28px; background: url('/data/attachments/smilies/harold-1.png') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie71
{
	width: 28px; height: 28px; background: url('/data/attachments/smilies/harold-6.png') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie68
{
	width: 28px; height: 28px; background: url('/data/attachments/smilies/harold-5.png') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie65
{
	width: 28px; height: 28px; background: url('/data/attachments/smilies/harold-2.png') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie67
{
	width: 28px; height: 28px; background: url('/data/attachments/smilies/harold-4.png') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie74
{
	width: 28px; height: 28px; background: url('/data/attachments/smilies/oscar-3.png') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie72
{
	width: 28px; height: 28px; background: url('/data/attachments/smilies/oscar-1.png') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie77
{
	width: 28px; height: 28px; background: url('/data/attachments/smilies/oscar-6.png') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie76
{
	width: 28px; height: 28px; background: url('/data/attachments/smilies/oscar-5.png') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie73
{
	width: 28px; height: 28px; background: url('/data/attachments/smilies/oscar-2.png') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie75
{
	width: 28px; height: 28px; background: url('/data/attachments/smilies/oscar-4.png') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie80
{
	width: 28px; height: 28px; background: url('/data/attachments/smilies/ulrika-3.png') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie78
{
	width: 28px; height: 28px; background: url('/data/attachments/smilies/ulrika-1.png') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie83
{
	width: 28px; height: 28px; background: url('/data/attachments/smilies/ulrika-6.png') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie82
{
	width: 28px; height: 28px; background: url('/data/attachments/smilies/ulrika-5.png') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie79
{
	width: 28px; height: 28px; background: url('/data/attachments/smilies/ulrika-2.png') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie81
{
	width: 28px; height: 28px; background: url('/data/attachments/smilies/ulrika-4.png') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie86
{
	width: 28px; height: 28px; background: url('/data/attachments/smilies/ylva-3.png') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie84
{
	width: 28px; height: 28px; background: url('/data/attachments/smilies/ylva-1.png') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie88
{
	width: 28px; height: 28px; background: url('/data/attachments/smilies/ylva-5.png') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie85
{
	width: 28px; height: 28px; background: url('/data/attachments/smilies/ylva-2.png') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie87
{
	width: 28px; height: 28px; background: url('/data/attachments/smilies/ylva-4.png') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie163
{
	width: 120px; height: 120px; background: url('/data/attachments/smilies/birthday/95.png') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie166
{
	width: 120px; height: 120px; background: url('/data/attachments/smilies/birthday/2k31.png') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie161
{
	width: 120px; height: 120px; background: url('/data/attachments/smilies/birthday/XP01.png') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie165
{
	width: 120px; height: 120px; background: url('/data/attachments/smilies/birthday/XP01B.png') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie167
{
	width: 120px; height: 120px; background: url('/data/attachments/smilies/birthday/XP01C.png') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie174
{
	width: 120px; height: 120px; background: url('/data/attachments/smilies/birthday/XP01E.png') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie162
{
	width: 120px; height: 120px; background: url('/data/attachments/smilies/birthday/XP02.png') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie164
{
	width: 120px; height: 120px; background: url('/data/attachments/smilies/birthday/XP03.png') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie172
{
	width: 120px; height: 120px; background: url('/data/attachments/smilies/birthday/VXA01.png') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie160
{
	width: 120px; height: 120px; background: url('/data/attachments/smilies/birthday/VXA02.png') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie173
{
	width: 120px; height: 120px; background: url('/data/attachments/smilies/birthday/VXA04.png') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie156
{
	width: 120px; height: 120px; background: url('/data/attachments/smilies/birthday/Harold01.png') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie157
{
	width: 120px; height: 120px; background: url('/data/attachments/smilies/birthday/Harold02.png') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie158
{
	width: 120px; height: 120px; background: url('/data/attachments/smilies/birthday/Harold03.png') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie159
{
	width: 120px; height: 120px; background: url('/data/attachments/smilies/birthday/Harold04.png') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie98
{
	width: 70px; height: 20px; background: url('/data/attachments/smilies/Kao4.gif') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie111
{
	width: 72px; height: 20px; background: url('/data/attachments/smilies/Kao18.gif') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie102
{
	width: 67px; height: 20px; background: url('/data/attachments/smilies/Kao7.gif') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie99
{
	width: 67px; height: 20px; background: url('/data/attachments/smilies/Kao5.gif') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie103
{
	width: 72px; height: 20px; background: url('/data/attachments/smilies/Kao8.gif') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie105
{
	width: 77px; height: 20px; background: url('/data/attachments/smilies/Kao10.gif') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie108
{
	width: 64px; height: 20px; background: url('/data/attachments/smilies/Kao13.gif') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie107
{
	width: 75px; height: 20px; background: url('/data/attachments/smilies/Kao12.gif') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie106
{
	width: 80px; height: 20px; background: url('/data/attachments/smilies/Kao11.gif') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie100
{
	width: 73px; height: 20px; background: url('/data/attachments/smilies/Kao3.gif') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie97
{
	width: 71px; height: 20px; background: url('/data/attachments/smilies/Kao2.gif') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie114
{
	width: 79px; height: 20px; background: url('/data/attachments/smilies/Kao22.gif') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie113
{
	width: 80px; height: 20px; background: url('/data/attachments/smilies/Kao21.gif') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie101
{
	width: 79px; height: 20px; background: url('/data/attachments/smilies/Kao6.gif') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie104
{
	width: 76px; height: 20px; background: url('/data/attachments/smilies/Kao9.gif') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie110
{
	width: 79px; height: 20px; background: url('/data/attachments/smilies/Kao15.gif') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie96
{
	width: 67px; height: 20px; background: url('/data/attachments/smilies/Kao1.gif') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie109
{
	width: 52px; height: 20px; background: url('/data/attachments/smilies/Kao14.gif') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie112
{
	width: 72px; height: 20px; background: url('/data/attachments/smilies/Kao19.gif') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie115
{
	width: 66px; height: 20px; background: url('/data/attachments/smilies/Kao23.gif') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie13
{
	width: 19px; height: 19px; background: url('/data/attachments/smilies/default_smile.gif') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie19
{
	width: 19px; height: 19px; background: url('/data/attachments/smilies/default_mad.gif') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie40
{
	width: 17px; height: 18px; background: url('/data/attachments/smilies/default_barf.gif') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie38
{
	width: 20px; height: 19px; background: url('/data/attachments/smilies/default_beard.gif') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie14
{
	width: 19px; height: 19px; background: url('/data/attachments/smilies/default_biggrin.gif') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie24
{
	width: 19px; height: 19px; background: url('/data/attachments/smilies/default_face.gif') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie42
{
	width: 17px; height: 17px; background: url('/data/attachments/smilies/default_blink.gif') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie41
{
	width: 19px; height: 19px; background: url('/data/attachments/smilies/default_blush.gif') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie15
{
	width: 19px; height: 19px; background: url('/data/attachments/smilies/default_shades.gif') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie34
{
	width: 19px; height: 19px; background: url('/data/attachments/smilies/default_cutesmile.gif') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie25
{
	width: 19px; height: 19px; background: url('/data/attachments/smilies/default_distrust.gif') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie35
{
	width: 17px; height: 17px; background: url('/data/attachments/smilies/default_dizzy.gif') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie20
{
	width: 24px; height: 22px; background: url('/data/attachments/smilies/default_supermad.gif') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie28
{
	width: 17px; height: 17px; background: url('/data/attachments/smilies/default_headshake.gif') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie33
{
	width: 23px; height: 25px; background: url('/data/attachments/smilies/default_kiss.gif') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie29
{
	width: 21px; height: 19px; background: url('/data/attachments/smilies/default_guffaw.gif') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie47
{
	width: 29px; height: 25px; background: url('/data/attachments/smilies/default_mrsatan.gif') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie36
{
	width: 19px; height: 19px; background: url('/data/attachments/smilies/default_ninja.gif') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie32
{
	width: 23px; height: 25px; background: url('/data/attachments/smilies/default_popcorn.gif') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie43
{
	width: 17px; height: 19px; background: url('/data/attachments/smilies/default_razz.gif') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie30
{
	width: 15px; height: 16px; background: url('/data/attachments/smilies/default_rock-left.gif') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie31
{
	width: 15px; height: 16px; background: url('/data/attachments/smilies/default_rock-right.gif') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie17
{
	width: 19px; height: 19px; background: url('/data/attachments/smilies/default_sad.gif') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie21
{
	width: 14px; height: 22px; background: url('/data/attachments/smilies/default_shock.gif') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie16
{
	width: 19px; height: 19px; background: url('/data/attachments/smilies/default_side.gif') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie39
{
	width: 20px; height: 19px; background: url('/data/attachments/smilies/default_stache.gif') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie26
{
	width: 19px; height: 19px; background: url('/data/attachments/smilies/default_stare.gif') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie22
{
	width: 19px; height: 19px; background: url('/data/attachments/smilies/default_tongue.gif') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie45
{
	width: 15px; height: 16px; background: url('/data/attachments/smilies/default_thumbsup-left.gif') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie46
{
	width: 15px; height: 16px; background: url('/data/attachments/smilies/default_thumbsup-right.gif') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie37
{
	width: 19px; height: 19px; background: url('/data/attachments/smilies/default_troll.gif') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie27
{
	width: 19px; height: 19px; background: url('/data/attachments/smilies/default_unsure.gif') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie23
{
	width: 19px; height: 19px; background: url('/data/attachments/smilies/default_wink.gif') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie44
{
	width: 20px; height: 19px; background: url('/data/attachments/smilies/default_wub.gif') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie1
{
	width: 18px; height: 18px; background: url('styles/default/xenforo/xenforo-smilies-sprite.png') no-repeat 0px 0px;
}

img.mceSmilieSprite.mceSmilie2
{
	width: 18px; height: 18px; background: url('styles/default/xenforo/xenforo-smilies-sprite.png') no-repeat -60px -21px;
}

img.mceSmilieSprite.mceSmilie3
{
	width: 18px; height: 18px; background: url('styles/default/xenforo/xenforo-smilies-sprite.png') no-repeat -40px -42px;
}

img.mceSmilieSprite.mceSmilie4
{
	width: 18px; height: 18px; background: url('styles/default/xenforo/xenforo-smilies-sprite.png') no-repeat -60px 0px;
}

img.mceSmilieSprite.mceSmilie5
{
	width: 18px; height: 18px; background: url('styles/default/xenforo/xenforo-smilies-sprite.png') no-repeat -40px -21px;
}

img.mceSmilieSprite.mceSmilie6
{
	width: 18px; height: 18px; background: url('styles/default/xenforo/xenforo-smilies-sprite.png') no-repeat -40px 0px;
}

img.mceSmilieSprite.mceSmilie7
{
	width: 18px; height: 18px; background: url('styles/default/xenforo/xenforo-smilies-sprite.png') no-repeat -20px -21px;
}

img.mceSmilieSprite.mceSmilie8
{
	width: 18px; height: 18px; background: url('styles/default/xenforo/xenforo-smilies-sprite.png') no-repeat -20px 0px;
}

img.mceSmilieSprite.mceSmilie9
{
	width: 18px; height: 18px; background: url('styles/default/xenforo/xenforo-smilies-sprite.png') no-repeat -20px -42px;
}

img.mceSmilieSprite.mceSmilie10
{
	width: 18px; height: 18px; background: url('styles/default/xenforo/xenforo-smilies-sprite.png') no-repeat 0px -42px;
}

img.mceSmilieSprite.mceSmilie11
{
	width: 18px; height: 18px; background: url('styles/default/xenforo/xenforo-smilies-sprite.png') no-repeat 0px -21px;
}

img.mceSmilieSprite.mceSmilie12
{
	width: 18px; height: 18px; background: url('styles/default/xenforo/xenforo-smilies-sprite.png') no-repeat -80px -42px;
}


/* Add a white background to kaomoji (dark theme only) */
/* These classes are auto-generated and might change if more smilies are added */
/*
img.mceSmilieSprite.mceSmilie96,
img.mceSmilieSprite.mceSmilie97,
img.mceSmilieSprite.mceSmilie98,
img.mceSmilieSprite.mceSmilie99,
img.mceSmilieSprite.mceSmilie100,
img.mceSmilieSprite.mceSmilie101,
img.mceSmilieSprite.mceSmilie102,
img.mceSmilieSprite.mceSmilie103,
img.mceSmilieSprite.mceSmilie104,
img.mceSmilieSprite.mceSmilie105,
img.mceSmilieSprite.mceSmilie106,
img.mceSmilieSprite.mceSmilie107,
img.mceSmilieSprite.mceSmilie108,
img.mceSmilieSprite.mceSmilie109,
img.mceSmilieSprite.mceSmilie110,
img.mceSmilieSprite.mceSmilie111,
img.mceSmilieSprite.mceSmilie112,
img.mceSmilieSprite.mceSmilie113,
img.mceSmilieSprite.mceSmilie114,
img.mceSmilieSprite.mceSmilie115 {background-color:#FFF; border-radius:2px;}
*/

.visibleResponsiveFull { display: inherit !important; }

.visibleResponsiveWide,
.visibleResponsiveMedium,
.visibleResponsiveNarrow { display: none !important; }

.hiddenResponsiveFull { display: none !important; } 

.hiddenResponsiveWide,
.hiddenResponsiveMedium,
.hiddenResponsiveNarrow { display: inherit !important; }


@media (max-width:800px)
{
	.Responsive .visibleResponsiveFull { display: none !important; }
	
	.Responsive .hiddenResponsiveFull { display: inherit !important; }
	
	.Responsive .hiddenWideUnder { display: none !important; }
}
@media (min-width:611px) AND (max-width:800px)
{
	.Responsive .visibleResponsiveWide { display: inherit !important; }
	
	.Responsive .hiddenResponsiveWide { display: none !important; }
	}

@media (min-width:481px) AND (max-width:610px)
{
	.Responsive .visibleResponsiveMedium { display: inherit !important; }
	
	.Responsive .hiddenResponsiveMedium { display: none !important; }
	
	.Responsive .hiddenWideUnder,
	.Responsive .hiddenMediumUnder { display: none !important; }
}

@media (max-width:480px)
{
	.Responsive .visibleResponsiveNarrow { display: inherit !important; }
	
	.Responsive .hiddenResponsiveNarrow { display: none !important; }
	
	.Responsive .hiddenWideUnder,
	.Responsive .hiddenMediumUnder,
	.Responsive .hiddenNarrowUnder { display: none !important; }
}

@media (max-width:610px)
{
	.Responsive .threeColumnList li
	{
		float: none;
		width: auto;
		margin: 2px 1% 2px 0;
	}
}

@media (max-width:480px)
{
	.Responsive .xenTooltip.statusTip
	{
		width: auto;
	}
	
	.Responsive .xenPreviewTooltip
	{
		box-sizing: border-box;
		width: auto;
		max-width: 100%;
	}
	
	.Responsive .xenPreviewTooltip .arrow
	{
		display: none;
	}
	
	.Responsive .previewTooltip .avatar
	{
		display: none;
	}
	
	.Responsive .previewTooltip .text
	{
		margin-left: 0;
	}
}




/* --- form.css --- */

/** Forms **/

.xenForm
{
	margin: 10px auto;
	max-width: 800px;
}

	.xenOverlay .xenForm
	{
		max-width: 600px;
	}

.xenForm .ctrlUnit > dd
{
	width: 68%;
	box-sizing: border-box;
	padding-right: 30px;
}

.xenForm .ctrlUnit > dd .textCtrl
{
	box-sizing: border-box;
	width: 100%;
}

	.xenForm .ctrlUnit > dd .textCtrl.indented
	{
		width: calc(100% - 16px);
	}

	.xenForm .ctrlUnit > dd .textCtrl[size],
	.xenForm .ctrlUnit > dd .textCtrl.autoSize
	{
		width: auto !important;
		min-width: 0;
	}

	.xenForm .ctrlUnit > dd .textCtrl.number
	{
		width: 150px;
	}


.xenForm > .sectionHeader:first-child,
.xenForm > fieldset > .sectionHeader:first-child
{
	margin-top: 0;
}

/** Sections **/

.xenForm fieldset,
.xenForm .formGroup
{
	border-top: 1px solid #D7EDFC;
	margin: 20px auto;
}

.xenForm > fieldset:first-child,
.xenForm > .formGroup:first-child
{
	border-top: none;
	margin: auto;
}

.xenForm .PreviewContainer + fieldset,
.xenForm .PreviewContainer + .formGroup
{
	border-top: none;
}

.xenForm fieldset + .ctrlUnit,
.xenForm .formGroup + .ctrlUnit,
.xenForm .submitUnit
{
	border-top: 1px solid #D7EDFC;
}

.xenForm fieldset + .ctrlUnit,
.xenForm .formGroup + .ctrlUnit
{
	padding-top: 10px;
}

.xenForm .primaryContent + .submitUnit,
.xenForm .secondaryContent + .submitUnit
{
	margin-top: 0;
	border-top: none;
}

.xenForm .ctrlUnit.submitUnit dd
{	
	line-height: 31px;
	padding-top: 0;
}

	.ctrlUnit.submitUnit dd .explain,
	.ctrlUnit.submitUnit dd .text,
	.ctrlUnit.submitUnit dd label
	{
		line-height: 1.28;
	}

/* now undo that */

.xenOverlay .ctrlUnit.submitUnit dd,
.Menu .ctrlUnit.submitUnit dd,
#QuickSearch .ctrlUnit.submitUnit dd
{
	border: none;
	background: none;
}

.xenForm .ctrlUnit
{
	
}

	.xenForm .ctrlUnit.limited
	{
		display: none;
	}

	/** Sections Immediately Following Headers **/

	.xenForm .sectionHeader + fieldset,
	.xenForm .heading + fieldset,
	.xenForm .subHeading + fieldset,
	.xenForm .sectionHeader + .formGroup,
	.xenForm .heading + .formGroup,
	.xenForm .subHeading + .formGroup
	{
		border-top: none;
		margin-top: 0;
	}
	
.xenForm .formHiderHeader
{
	margin: 10px;
	font-size: 15px;
	font-weight: bold;
}


/** *********************** **/
/** TEXT INPUTS             **/
/** *********************** **/

.textCtrl
{
	font-size: 13px;
font-family: Verdana,"Segoe UI",Arial,sans-serif;
color: #000000;
background-color: #FCFCFF;
padding: 3px;
margin-bottom: 2px;
border-width: 1px;
border-style: solid;
border-top-color:  rgb(127,127,127); border-top-color:  rgba(127,127,127, 0.5); _border-top-color:  rgb(127,127,127);
border-right-color:  rgb(127,127,127); border-right-color:  rgba(127,127,127, 0.25); _border-right-color:  rgb(127,127,127);
border-bottom-color:  rgb(127,127,127); border-bottom-color:  rgba(127,127,127, 0.25); _border-bottom-color:  rgb(127,127,127);
border-left-color:  rgb(127,127,127); border-left-color:  rgba(127,127,127, 0.5); _border-left-color:  rgb(127,127,127);
border-radius: 4px;
outline: 0;

}

select.textCtrl
{
	word-wrap: normal;
	-webkit-appearance: menulist;
}

select[multiple].textCtrl,
select[size].textCtrl
{
	-webkit-appearance: listbox;
}

select[size="0"].textCtrl,
select[size="1"].textCtrl
{
	-webkit-appearance: menulist;
}

textarea.textCtrl
{
	word-wrap: break-word;
	resize: vertical;
}

	.textCtrl:focus,
	.textCtrl.Focus
	{
		background-color: #F0F7FC;
border-color:  rgb(127,127,127); border-color:  rgba(127,127,127, 0.66); _border-color:  rgb(127,127,127);
background-image: linear-gradient(#D7EDFC,#FFFFFF);

	}	

	textarea.textCtrl:focus
	{
		
	}

	input.textCtrl.disabled,
	textarea.textCtrl.disabled,
	.disabled .textCtrl
	{
		font-style: italic;
color: rgb(100,100,100);
background-color: rgb(245,245,245);

	}
	
	.textCtrl.prompt
	{
		font-style: italic;
color: rgb(160,160,160);

	}
	
	.textCtrl:-moz-placeholder
	{
		/* needs to be in its own rule due to weird selector */
		font-style: italic;
color: rgb(160,160,160);

	}
	
	.textCtrl::-moz-placeholder
	{
		/* needs to be in its own rule due to weird selector */
		font-style: italic;
color: rgb(160,160,160);

	}

	.textCtrl::-webkit-input-placeholder
	{
		/* needs to be in its own rule due to weird selector */
		font-style: italic;
color: rgb(160,160,160);

	}
	
	.textCtrl:-ms-input-placeholder
	{
		/* needs to be in its own rule due to weird selector */
		font-style: italic;
color: rgb(160,160,160);

	}
	
	.textCtrl.autoSize
	{
		width: auto !important;
	}

	.textCtrl.number,
	.textCtrl.number input
	{
		text-align: right;
		width: 150px;
	}
	
	.textCtrl.fillSpace
	{
		width: 100%;
		box-sizing: border-box;
		_width: 95%;
	}

	.textCtrl.code,
	.textCtrl.code input
	{
		font-family: Consolas,"Courier New",Courier,monospace;
white-space: pre;
word-wrap: normal;
direction: ltr;

	}
	
	input.textCtrl[type="password"]
	{
		font-family: Verdana, Geneva, Arial, Helvetica, sans-serif;
	}

	input[type="email"],
	input[type="url"]
	{
		direction: ltr;
	}

	.textCtrl.titleCtrl,
	.textCtrl.titleCtrl input
	{
		font-size: 18pt;
	}

textarea.textCtrl.Elastic
{
	/* use for jQuery.elastic */
	max-height: 300px;
}

/* for use with wrapped inputs */
.textCtrlWrap
{
	display: inline-block;
}

.textCtrlWrap input.textCtrl
{
	padding: 0 !important;
	margin: 0 !important;
	border: none !important;
	background: transparent !important;
	border-radius: 0 !important;
}

.textCtrlWrap.blockInput input.textCtrl
{
	border-top:  1px solid rgb(127,127,127) !important; border-top:  1px solid rgba(127,127,127, 0.5) !important; _border-top:  1px solid rgb(127,127,127) !important;
	margin-top: 4px !important;
}

.taggingInput.textCtrl
{
	padding-top: 1px;
	min-height: 25px;
}

.taggingInput input
{
	margin: 0px;
	font-size: 12px;
	border: 1px solid transparent;
	padding: 0;
	background: transparent;
	outline: 0;
	color: inherit;
	font-family: inherit;
}

.taggingInput .tag
{
	border: 1px solid #CFE3F1;
	border-radius: 3px;
	display: inline-block;
	padding: 0 3px;
	text-decoration: none;
	background-color:#D7EDFC;
	background-image:linear-gradient(#CFE3F1,#D7EDFC);
	color: #176093;
	margin-right: 3px;
	margin-top: 2px;
	font-size: 12px;
	max-width: 98%;
	box-shadow: 1px 1px 3px rgba(0,0,0, 0.25);
}

.disabled.taggingInput .tag
{
	opacity: 0.7;
}

	.disabled.taggingInput .tag a
	{
		pointer-events: none;
	}

	html .taggingInput .tag a
	{
		color: #6CB2E4;
		font-weight: bold;
		text-decoration: none;
	}

.taggingInput .addTag
{
	display: inline-block;
	min-width: 150px;
	max-width: 100%;
	margin-top: 2px;
}

.taggingInput .tagsClear
{
	clear: both;
	width: 100%;
	height: 0px;
	float: none;
}

/** *********************** **/
/** BUTTONS                 **/
/** *********************** **/

.button
{
	font-style: normal;
	
	font-size: 12px;
font-family: Tahoma,Roboto,Arial,sans-serif;
color: #FCFCFF;
background-color: #141414;
padding: 0 1em;
border-radius: 4px;
display: inline-block;
box-sizing: border-box;
text-align: center;
box-shadow: 0 1px 4px 0 rgba(0,0,0,0.3);
border: none!important;
outline: none;
cursor: pointer;
line-height: 2.5em;
height: 2.5em;

}

.button.smallButton
{
	font-size: 11px;
	padding: 0px 4px;
	line-height: 21px;
	height: 21px;
	border-radius: 5px;
}

.button.primary
{
	background-color: #000000;

}

input.button.disabled,
a.button.disabled,
input.button.primary.disabled,
a.button.primary.disabled,
html .buttonProxy .button.disabled
{
	color: #999;
background-color: #EEE;
border-color: #CCC;
box-shadow: 0 0 0 transparent;

}

	.button::-moz-focus-inner
	{
		border: none;
	}

	a.button
	{
		display: inline-block;
		color: #FCFCFF;
	}

	.button:hover,
	.button[href]:hover,
	.buttonProxy:hover .button
	{
		color: #FCFCFF;
text-decoration: none;
background-color: #176093;
box-shadow: none;

	}

	.button:focus
	{
		border-color: #6CB2E4;

	}

	.button:active,
	.button[href]:active,
	.button.ToggleButton.checked,
	.buttonProxy:active .button
	{
		color: black;
background-color: rgb(153, 153, 163);
border-color: rgb(200,200,215);
border-top-color: #b3b3bd;
border-bottom-color: white;
box-shadow: none;
outline: 0;

	}

	.button.ToggleButton
	{
		cursor: default;
		width: auto;
		color: ;
	}
	
	.button.ToggleButton.checked
	{
		background-color: rgb(255,150,50);
	}

	.button.inputSupplementary
	{
		width: 25px;
		position: absolute;
		top: 0px;
		right: 0px;
	}

	.button.inputSupplementary.add
	{
		color: green;
	}

	.button.inputSupplementary.delete
	{
		color: red;
	}

	.submitUnit .button
	{
		min-width: 100px;
		*min-width: 0;
	}

















/** Control Units **/

.xenForm .ctrlUnit
{
	position: relative;
	margin: 10px auto;
}

/* clearfix */ .xenForm .ctrlUnit { zoom: 1; } .xenForm .ctrlUnit:after { content: '.'; display: block; height: 0; clear: both; visibility: hidden; }

.xenForm .ctrlUnit.fullWidth
{
	overflow: visible;
}

/** Control Unit Labels **/

.xenForm .ctrlUnit > dt
{
	padding-top: 4px;
padding-right: 15px;
text-align: right;
vertical-align: top;

	box-sizing: border-box;
	width: 32%;
	float: left;
}

/* special long-text label */
.xenForm .ctrlUnit > dt.explain
{
	font-size: 11px;
	text-align: justify;
}


.xenForm .ctrlUnit.fullWidth dt,
.xenForm .ctrlUnit.submitUnit.fullWidth dt
{
	float: none;
	width: auto;
	text-align: left;
	height: auto;
}

.xenForm .ctrlUnit.fullWidth dt
{
	margin-bottom: 2px;
}

	.xenForm .ctrlUnit > dt label
	{
		margin-left: 30px;
	}

	/** Hidden Labels **/

	.xenForm .ctrlUnit.surplusLabel dt label
	{
		display: none;
	}

	/** Section Links **/

	.ctrlUnit.sectionLink dt
	{
		text-align: left;
		font-size: 11px;
	}

		.ctrlUnit.sectionLink dt a
		{
			margin-left: 11px; /*TODO: sectionHeader padding + border*/
		}		

	/** Hints **/

	.ctrlUnit > dt dfn
	{
		font-style: italic;
font-size: 10px;
color: #969696;
margin-left: 30px;
display: block;

	}
	
	.ctrlUnit.fullWidth dt dfn
	{
		display: inline;
		margin: 0;
	}
	
		.ctrlUnit > dt dfn b,
		.ctrlUnit > dt dfn strong
		{
			color: #646464;
		}

	/** Inline Errors **/

	.ctrlUnit > dt .error
	{
		font-size: 10px;
color: red;
display: block;

	}
	
	.ctrlUnit > dt dfn,
	.ctrlUnit > dt .error,
	.ctrlUnit > dt a
	{
		font-weight: normal;
	}

.xenForm .ctrlUnit.submitUnit dt
{
	height: 19px;
	display: block;
}

	.ctrlUnit.submitUnit dt.InProgress
	{
		background: transparent url('styles/default/xenforo/widgets/ajaxload.info_B4B4DC_facebook.gif') no-repeat center center;
	}

/** Control Holders **/

.xenForm .ctrlUnit > dd
{
	/*todo: kill property */
	
	float: left;
}

.xenForm .ctrlUnit.fullWidth > dd
{
	float: none;
	width: auto;
	padding-left: 30px;
}

/** Explanatory paragraph **/

.ctrlUnit > dd .explain
{
	font-size: 11px;
color: #969696;
margin-top: 2px;

	/*TODO:max-width: auto;*/
}
	
	.ctrlUnit > dd .explain b,
	.ctrlUnit > dd .explain strong
	{
		color: #646464;
	}

/** List items inside controls **/

.ctrlUnit > dd > * > li
{
	margin: 4px 0 8px;
	padding-left: 1px; /* fix a webkit display bug */
}

.ctrlUnit > dd > * > li:first-child > .textCtrl:first-child
{
	margin-top: -3px;
}

.ctrlUnit > dd .break
{
	margin-bottom: 0.75em;
	padding-bottom: 0.75em;
}

.ctrlUnit > dd .rule
{
	border-bottom: 1px solid #D7EDFC;
}

.ctrlUnit > dd .ddText
{
	margin-bottom: 2px;
}

/** Hints underneath checkbox / radio controls **/

.ctrlUnit > dd > * > li .hint
{
	font-size: 11px;
	color: #969696;
	margin-left: 16px;
	margin-top: 2px;
}

/** DISABLERS **/

.ctrlUnit > dd > * > li > ul,
.ctrlUnit .disablerList,
.ctrlUnit .indented
{
	margin-left: 16px;
}

.ctrlUnit > dd > * > li > ul > li:first-child
{
	margin-top: 6px;
}

.ctrlUnit > dd .disablerList > li,
.ctrlUnit > dd .checkboxColumns > li,
.ctrlUnit > dd .choiceList > li
{
	margin-top: 6px;
}
	
/** Other stuff... **/

.ctrlUnit > dd .helpLink
{
	font-size: 10px;
}

.ctrlUnit.textValue dt
{
	padding-top: 0px;
}

.button.spinBoxButton
{
	font-family: Verdana,"Segoe UI",Arial,Meiryo,sans-serif;
	font-size: 11pt;
}

.unitPairsJustified li
{
	overflow: hidden;
}

	.unitPairsJustified li .label
	{
		float: left;
	}
	
	.unitPairsJustified li .value
	{
		float: right;
	}

#calroot
{
	margin-top: -1px;
	width: 198px;
	padding: 2px;
	background-color: #FCFCFF;
	font-size: 11px;
	border: 1px solid #65A5D1;
	border-radius: 5px;
	box-shadow:0 5px 8px 1px rgba(0,0,0,0.6);
	z-index: 7500;
}

#calhead
{	
	padding: 2px 0;
	height: 22px;
} 

	#caltitle {
		font-size: 11pt;
		color: #65A5D1;
		float: left;
		text-align: center;
		width: 155px;
		line-height: 20px;
	}
	
	#calnext, #calprev {
		display: block;
		width: 20px;
		height: 20px;
		font-size: 11pt;
		line-height: 20px;
		text-align: center;
		float: left;
		cursor: pointer;
	}

	#calnext {
		float: right;
	}

	#calprev.caldisabled, #calnext.caldisabled {
		visibility: hidden;	
	}

#caldays {
	height: 14px;
	border-bottom: 1px solid #65A5D1;
}

	#caldays span {
		display: block;
		float: left;
		width: 28px;
		text-align: center;
		color: #65A5D1;
	}

#calweeks {
	margin-top: 4px;
}

.calweek {
	clear: left;
	height: 22px;
}

	.calweek a {
		display: block;
		float: left;
		width: 27px;
		height: 20px;
		text-decoration: none;
		font-size: 11px;
		margin-left: 1px;
		text-align: center;
		line-height: 20px;
		border-radius: 3px;
	} 
	
		.calweek a:hover, .calfocus {
			background-color: #F0F7FC;
		}

a.caloff {
	color: #969696;		
}

a.caloff:hover {
	background-color: #F0F7FC;		
}

a.caldisabled {
	background-color: #efefef !important;
	color: #ccc	!important;
	cursor: default;
}

#caltoday {
	font-weight: bold;
}

#calcurrent {
	background-color: #65A5D1;
	color: #F0F7FC;
}
ul.autoCompleteList
{
	background-color: #F0F7FC;
	
	border: 1px solid #6CB2E4;
	padding: 2px;
	
	font-size: 11px;
	
	min-width: 180px;
	_width: 180px;
	
	z-index: 1000;
}

ul.autoCompleteList li
{
	padding: 3px 3px;
	height: 24px;
	line-height: 24px;
}

ul.autoCompleteList li:hover,
ul.autoCompleteList li.selected
{
	background-color: #D7EDFC;
	border-radius: 3px;
}

ul.autoCompleteList img.autoCompleteAvatar
{
	float: left;
	margin-right: 3px;
	width: 24px;
	height: 24px;
}

ul.autoCompleteList li strong
{
	font-weight: bold;
}

/** status editor **/

.statusEditorCounter
{
	color: green;
}

.statusEditorCounter.warning
{
	color: orange;
	font-weight: bold;
}

.statusEditorCounter.error
{
	color: red;
	font-weight: bold;
}

.explain .statusHeader
{
	display: inline;
}

.explain .CurrentStatus
{
	color: #141414;
	font-style: italic;
	padding-left: 5px;
}

/* BB code-based editor styling */

.xenForm .ctrlUnit.fullWidth dd .bbCodeEditorContainer textarea
{
	margin-left: 0;
	min-height: 200px;
}

.bbCodeEditorContainer a
{
	font-size: 11px;
}

/*
 * Fix silly top padding. This may require additional tags in the padding-top selector.
 */

.xenForm .ctrlUnit > dd
{
	padding-top: 4px;
}

	.xenForm .ctrlUnit.fullWidth > dd
	{
		padding-top: 0;
	}

.xenForm .ctrlUnit > dd > input,
.xenForm .ctrlUnit > dd > select,
.xenForm .ctrlUnit > dd > textarea,
.xenForm .ctrlUnit > dd > ul,
.xenForm .ctrlUnit > dd > .verticalShift
{
	margin-top: -4px;
}

	.xenForm .ctrlUnit.fullWidth > dd > input,
	.xenForm .ctrlUnit.submitUnit > dd > input,
	.xenForm .ctrlUnit.fullWidth > dd > select,
	.xenForm .ctrlUnit.submitUnit > dd > select,
	.xenForm .ctrlUnit.fullWidth > dd > textarea,
	.xenForm .ctrlUnit.submitUnit > dd > textarea,
	.xenForm .ctrlUnit.fullWidth > dd > ul,
	.xenForm .ctrlUnit.submitUnit > dd > ul
	{
		margin-top: 0;
	}
	
/*
 * Multi-column checkboxes
 */
 
.xenForm .checkboxColumns > dd > ul,
ul.checkboxColumns
{
	-webkit-column-count : 2; -moz-column-count : 2;column-count: 2;
	-webkit-column-gap : 8px; -moz-column-gap : 8px;column-gap: 8px;
}

	.xenForm .checkboxColumns > dd > ul li,
	ul.checkboxColumns li
	{
		-webkit-column-break-inside : avoid; -moz-column-break-inside : avoid;column-break-inside: avoid;
		break-inside: avoid-column;
		margin-bottom: 4px;
		padding-left: 1px;
		display: inline-block;
		width: 100%;
	}
	
	.xenForm .checkboxColumns.blockLinksList > dd > ul li,
	ul.checkboxColumns.blockLinksList li
	{
		display: block;
	}

.xenForm .checkboxColumns.multiple > dd > ul
{
	-webkit-column-count : auto; -moz-column-count : auto;column-count: auto;
	-webkit-column-gap : normal; -moz-column-gap : normal;column-gap: normal;
}

.xenForm .checkboxColumns.multiple > dd
{
	-webkit-column-count : 2; -moz-column-count : 2;column-count: 2;
	-webkit-column-gap : 8px; -moz-column-gap : 8px;column-gap: 8px;
}

.xenForm .checkboxColumns.multiple > dd > ul
{
	margin-bottom: 18px;
}

#recaptcha_image
{
	box-sizing: content-box;
	max-width: 100%;
}

#recaptcha_image img
{
	max-width: 100%;
}

#helper_birthday { display: inline-block; }
#helper_birthday > li
{
	display: inline;
}
html[dir=rtl] #helper_birthday input,
html[dir=rtl] #helper_birthday select
{
	direction: rtl;
}


@media (max-width:480px)
{
	.Responsive .xenForm .ctrlUnit > dt
	{
		float: none;
		width: auto;
		text-align: left;
		height: auto;
	}

		.Responsive .xenForm .ctrlUnit > dt label,
		.Responsive .xenForm .ctrlUnit > dt dfn
		{
			margin-left: 0;
		}

	.Responsive .xenForm .ctrlUnit.submitUnit dt
	{
		height: auto;
	}

	.Responsive .xenForm .ctrlUnit > dd,
	.Responsive .xenForm .ctrlUnit.fullWidth dd
	{
		float: none;
		width: auto;
		text-align: left;
		height: auto;
		padding-left: 10px;
		padding-right: 10px;
		overflow: hidden;
	}

	.Responsive .xenForm .checkboxColumns > dd > ul,
	.Responsive ul.checkboxColumns
	{
		-webkit-column-count : 1; -moz-column-count : 1;column-count: 1;
	}
	
	.Responsive #ctrl_upload
	{
		max-width: 200px;
	}
	
	.Responsive .xenForm .ctrlUnit > dd .textCtrl[size],
	.Responsive .xenForm .ctrlUnit > dd .textCtrl.autoSize
	{
		width: 100% !important;
	}
	
	.Responsive .xenForm .ctrlUnit > dd > input,
	.Responsive .xenForm .ctrlUnit > dd > select,
	.Responsive .xenForm .ctrlUnit > dd > textarea,
	.Responsive .xenForm .ctrlUnit > dd > ul,
	.Responsive .xenForm .ctrlUnit > dd > .verticalShift
	{
		margin-top: 0;
	}
}

@media (max-width:610px)
{
	.Responsive .insideSidebar .xenForm .ctrlUnit > dt
	{
		float: none;
		width: auto;
		text-align: left;
		height: auto;
	}

		.Responsive .insideSidebar .xenForm .ctrlUnit > dt label,
		.Responsive .insideSidebar .xenForm .ctrlUnit > dt dfn
		{
			margin-left: 0;
		}

	.Responsive .insideSidebar .xenForm .ctrlUnit.submitUnit dt
	{
		height: auto;
	}

	.Responsive .insideSidebar .xenForm .ctrlUnit > dd,
	.Responsive .insideSidebar .xenForm .ctrlUnit.fullWidth dd
	{
		float: none;
		width: auto;
		text-align: left;
		height: auto;
		padding-left: 10px;
		padding-right: 10px;
		overflow: hidden;
	}
	
	.Responsive .insideSidebar .xenForm .ctrlUnit > dd .textCtrl[size],
	.Responsive .insideSidebar .xenForm .ctrlUnit > dd .textCtrl.autoSize
	{
		width: 100% !important;
	}
	
	.Responsive .insideSidebar .xenForm .ctrlUnit > dd > input,
	.Responsive .insideSidebar .xenForm .ctrlUnit > dd > select,
	.Responsive .insideSidebar .xenForm .ctrlUnit > dd > textarea,
	.Responsive .insideSidebar .xenForm .ctrlUnit > dd > ul
	{
		margin-top: -0;
	}
}

@media (max-device-width:568px)
{
	.Responsive .textCtrl,
	.Responsive .taggingInput input,
	.Responsive .taggingInput .tag
	{
		font-size: 16px;
	}
}


/* --- public.css --- */

#header
{
	font-size: 18px;
font-family: Tahoma,Roboto,"Segoe UI",Arial,sans-serif;
background-color: #1B1F20;

}

/* clearfix */ #header .pageWidth .pageContent { zoom: 1; } #header .pageWidth .pageContent:after { content: '.'; display: block; height: 0; clear: both; visibility: hidden; }

	#logo
	{
		display: block;
		float: left;
		line-height: 81px;
		height: 81px;
		max-width: 100%;
		vertical-align: middle;
	}

		/* IE6/7 vertical align fix */
		#logo span
		{
			*display: inline-block;
			*height: 100%;
		}

		#logo a:hover
		{
			text-decoration: none;
		}

		#logo img
		{
			vertical-align: middle;
			max-width: 100%;
		}

	#visitorInfo
	{
		float: right;
		min-width: 250px;
		_width: 250px;
		overflow: hidden; zoom: 1;
		background: #CFE3F1;
		padding: 5px;
		border-radius: 5px;
		margin: 10px 0;
		border: 1px solid #032A46;
		color: #032A46;
	}

		#visitorInfo .avatar
		{
			float: left;
			display: block;
		}

			#visitorInfo .avatar .img
			{
				border-color: #65A5D1;
			}

		#visitorInfo .username
		{
			font-size: 18px;
			text-shadow: 1px 1px 10px white;
			color: #032A46;
			white-space: nowrap;
			word-wrap: normal;
		}

		#alerts
		{
			zoom: 1;
		}

		#alerts #alertMessages
		{
			padding-left: 5px;
		}

		#alerts li.alertItem
		{
			font-size: 11px;
		}

			#alerts .label
			{
				color: #032A46;
			}

.footer .pageContent
{
	font-size: 11px;
color: #CCC;
background-color: #333;
border-bottom-right-radius: 5px;
border-bottom-left-radius: 5px;
overflow: hidden;
zoom: 1;

}
	
	.footer a,
	.footer a:visited
	{
		color: #DDD;
padding: 5px;
display: block;

	}
	
		.footer a:hover,
		.footer a:active
		{
			color: #FFF;

		}

	.footer .choosers
	{
		padding-left: 5px;
float: left;
overflow: hidden;
zoom: 1;

	}
	
		.footer .choosers dt
		{
			display: none;
		}
		
		.footer .choosers dd
		{
			float: left;
			
		}
		
	.footerLinks
	{
		padding-right: 5px;
float: right;
overflow: hidden;
zoom: 1;

	}
	
		.footerLinks li
		{
			float: left;
			
		}
		
			.footerLinks a.globalFeed
			{
				width: 14px;
				height: 14px;
				display: block;
				text-indent: -9999px;
				white-space: nowrap;
				background: url('styles/default/xenforo/xenforo-ui-sprite.png') no-repeat -112px -16px;
				padding: 0;
				margin: 5px;
			}

.footerLegal .pageContent
{
	font-size: 11px;
	overflow: hidden; zoom: 1;
	padding: 5px 5px 15px;
	text-align: center;
}
	
	#copyright
	{
		color: #646464;
		float: left;
	}
	
	#legal
	{
		float: right;
	}
	
		#legal li
		{
			float: left;
			
			margin-left: 10px;
		}


@media (max-width:610px)
{
	.Responsive .footerLinks a.globalFeed,
	.Responsive .footerLinks a.topLink,
	.Responsive .footerLinks a.homeLink
	{
		display: none;
	}

	.Responsive .footerLegal .debugInfo
	{
		clear: both;
	}
}

@media (max-width:480px)
{
	.Responsive #copyright span
	{
		display: none;
	}
}


.breadBoxTop,
.breadBoxBottom
{
	padding: 10px 0;
overflow: hidden;
zoom: 1;
clear: both;
box-sizing: border-box;

}

/*.breadBoxTop {}*/

.breadBoxTop .topCtrl
{
	margin-left: 5px;
float: right;
line-height: 24px;

}

.breadcrumb
{
	font-size: 12px;
overflow: hidden;
zoom: 1;
/*max-width: 100%;*/
height: 24px;

}

.breadcrumb.showAll
{
	height: auto;
}

.breadcrumb .boardTitle
{
	
}

.breadcrumb .crust
{
	display: block;
float: left;
position: relative;
zoom: 1;
max-width: 50%;

}

.breadcrumb .crust a.crumb
{
	cursor: pointer;
	text-decoration: none;
padding: 0 5px 0 15px;
display: block;
outline: 0 none;
_border-bottom: none;
line-height: 24px;

}

	.breadcrumb .crust a.crumb > span
	{
		display: block;
		text-overflow: ellipsis;
		word-wrap: normal;
		white-space: nowrap;
		overflow: hidden;
		max-width: 100%;
	}

	.breadcrumb .crust:first-child a.crumb,
	.breadcrumb .crust.firstVisibleCrumb a.crumb
	{
		padding-left: 0;

	}
	
	.breadcrumb .crust:last-child a.crumb
	{
		font-weight: bold;

	}

.breadcrumb .crust .arrow
{
	border-color: transparent;

}

.breadcrumb .crust .arrow span
{
	
}

.breadcrumb .crust:hover a.crumb
{
	
}

.breadcrumb .crust:hover .arrow span
{
	border-left-color: ;
}

	.breadcrumb .crust .arrow
	{
		/* hide from IE6 */
		_display: none;
	}

.breadcrumb .jumpMenuTrigger
{
	background: transparent url('styles/default/xenforo/xenforo-ui-sprite.png') no-repeat 0 0;
margin-top: 6px;
margin-right: 5px;
display: block;
float: left;
white-space: nowrap;
text-indent: 9999px;
overflow: hidden;
width: 13px;
height: 13px;

}

.message_page .breadcrumb {display:none;}


@media (max-width:480px)
{
	.Responsive .breadBoxTop.withTopCtrl
	{
		display: table;
		table-layout: fixed;
		width: 100%;
	}

	.Responsive .breadBoxTop.withTopCtrl nav
	{
		display: table-header-group;
	}

	.Responsive .breadBoxTop.withTopCtrl .topCtrl
	{
		display: table-footer-group;
		margin-top: 5px;
		text-align: right;
	}
}


#navigation .pageContent
{
	height: 78px;
	position: relative;
}

#navigation .menuIcon
{
	position: relative;
	font-size:18px;
	width: 16px;
	display: inline-block;
	text-indent: -9999px;
}

#navigation .PopupOpen .menuIcon:before,
#navigation .navLink .menuIcon:before
{
	zoom: 1;
}

#navigation .menuIcon:before
{
	content: "";
	font-size: 18px;
	position: absolute;
	top: 0.8em;
	left: 0;
	width: 16px;
	height: 2px;
	border-top: 6px double currentColor;
	border-bottom: 2px solid currentColor;
}

	.navTabs
	{
		font-size: 14px;
background-color: #333;
border: 5px solid #333;

		
		height: 38px;
	}
	
		.navTabs .publicTabs
		{
			float: left;
		}
		
		.navTabs .visitorTabs
		{
			float: right;
		}
	
			.navTabs .navTab
			{
				float: left;
				white-space: nowrap;
				word-wrap: normal;
				
				
			}


/* ---------------------------------------- */
/* Links Inside Tabs */

.navTabs .navLink,
.navTabs .SplitCtrl
{
	background-color: #444;
display: block;
float: left;
color: #FFF!important;
vertical-align: text-bottom;
text-align: center;
outline: 0 none;
text-shadow: none;

	
	
	
	height: 38px;
	line-height: 38px;
}

	.navTabs .publicTabs .navLink
	{
		padding: 0 15px;
	}
	
	.navTabs .visitorTabs .navLink
	{
		padding: 0 10px;
	}
	
	.navTabs .navLink:hover
	{
		text-decoration: none;
	}
	
	/* ---------------------------------------- */
	/* unselected tab, popup closed */

	.navTabs .navTab.PopupClosed
	{
		position: relative;
	}
	
	.navTabs .navTab.PopupClosed .navLink
	{
		color: #CFE3F1;
	}
	
		.navTabs .navTab.PopupClosed:hover
		{
			background-color: #176093;
		}
		
			.navTabs .navTab.PopupClosed .navLink:hover
			{
				color: #FFFFFF;
			}
		
	.navTabs .navTab.PopupClosed .arrowWidget
	{
		/* circle-arrow-down-light */
		background-position: -64px 0;
	}
	
	.navTabs .navTab.PopupClosed .SplitCtrl
	{
		margin-left: -14px;
		width: 14px;
	}
		
		.navTabs .navTab.PopupClosed:hover .SplitCtrl
		{
			/* nav_menu_gadget, height: 17px */
			background: transparent url('styles/default/xenforo/xenforo-ui-sprite.png') no-repeat -128px 11.5px;
		}
	
	/* ---------------------------------------- */
	/* selected tab */

	.navTabs .navTab.selected .navLink
	{
		position: relative;
		background-color: #F0F7FC;
padding-top: 2px;
margin-top: -2px;
border: 1px solid #333;
color: #000000!important;
text-shadow: 0 0 3px #F0F7FC;

	}
	
	.navTabs .navTab.selected .SplitCtrl
	{
		display: none;
	}
	
	.navTabs .navTab.selected .arrowWidget
	{
		/* circle-arrow-down */
		background-position: -32px 0;
	}
	
		.navTabs .navTab.selected.PopupOpen .arrowWidget
		{
			/* circle-arrow-up */
			background-position: -16px 0;
		}
	
	/* ---------------------------------------- */
	/* unselected tab, popup open */
	
	.navTabs .navTab.PopupOpen .navLink
	{
	}
	
	
	/* ---------------------------------------- */
	/* selected tab, popup open (account) */
	
	.navTabs .navTab.selected.PopupOpen .navLink
	{
		border-top-left-radius: 3px;
border-top-right-radius: 3px;
border-bottom-right-radius: 0px;
border-bottom-left-radius: 0px;
/*text-shadow: 1px 1px 2px white;*/

	}
	
/* ---------------------------------------- */
/* Second Row */

.navTabs .navTab.selected .tabLinks
{
	background-color: #F0F7FC;
	
	width: 100%;	
	padding: 0;
	border: none;
	overflow: hidden; zoom: 1;	
	position: absolute;
	left: 0px;	
	top: 40px;
	height: 38px;
	background-position: 0px -38px;
	*clear:expression(style.width = document.getElementById('navigation').offsetWidth + 'px', style.clear = "none", 0);
}

	.navTabs .navTab.selected .blockLinksList
	{
		background: none;
		padding: 0;
		border: none;
		margin-left: 8px;
	}

	.withSearch .navTabs .navTab.selected .blockLinksList
	{
		margin-right: 275px;
	}

	.navTabs .navTab.selected .tabLinks .menuHeader
	{
		display: none;
	}
	
	.navTabs .navTab.selected .tabLinks li
	{
		float: left;
		padding: 2px 0;
	}
	
		.navTabs .navTab.selected .tabLinks a
		{
			font-size: 14px;
color: #176093;
padding: 1px 10px;
display: block;

			
			line-height: 32px;
		}
		
		.navTabs .navTab.selected .tabLinks .PopupOpen a
		{
			color: inherit;
			text-shadow: none;
		}
		
			.navTabs .navTab.selected .tabLinks a:hover,
			.navTabs .navTab.selected .tabLinks a:focus
			{
				color: #2B485C;
text-decoration: none;
background-color: #F0F7FC;
border-bottom: 2px solid #CFE3F1;
border-radius: 0;

			}
			
			.navTabs .navTab.selected .tabLinks .Popup a:hover,
			.navTabs .navTab.selected .tabLinks .Popup a:focus
			{
				color: inherit;
				background: none;
				border-color: transparent;
				border-radius: 0;
				text-shadow: none;
			}
	
/* ---------------------------------------- */
/* Alert Balloons */
	
.navTabs .navLink .itemCount
{
	font-weight: bold;
font-size: 9px;
color: white;
background-color: #e03030;
padding: 0 2px;
border-radius: 2px;
position: absolute;
right: 2px;
top: -12px;
line-height: 16px;
min-width: 12px;
_width: 12px;
text-align: center;
text-shadow: none;
white-space: nowrap;
word-wrap: normal;
box-shadow: 2px 2px 5px rgba(0,0,0, 0.25);
height: 16px;

}

	.navTabs .navLink .itemCount .arrow
	{
		border: 3px solid transparent;
border-top-color: #e03030;
border-bottom: 1px none black;
position: absolute;
bottom: -3px;
right: 4px;
line-height: 0px;
text-shadow: none;
_display: none;
/* Hide from IE6 */
width: 0px;
height: 0px;

	}
	
.navTabs .navLink .itemCount.Zero
{
	display: none;
}

.navTabs .navLink .itemCount.ResponsiveOnly
{
	display: none !important;
}

.NoResponsive #VisitorExtraMenu_Counter,
.NoResponsive #VisitorExtraMenu_ConversationsCounter,
.NoResponsive #VisitorExtraMenu_AlertsCounter
{
	display: none !important;
}
	
/* ---------------------------------------- */
/* Account Popup Menu */

.navTabs .navTab.account .navLink
{
	font-weight: bold;
}

	.navTabs .navTab.account .navLink .accountUsername
	{
		display: block;
		max-width: 100px;
		overflow: hidden;
		text-overflow: ellipsis;
	}

#AccountMenu
{
	width: 274px;
}

#AccountMenu .menuHeader
{
	position: relative;
}

	#AccountMenu .menuHeader .avatar
	{
		float: left;
		margin-right: 10px;
	}
	
	#AccountMenu .menuHeader h3,
	#AccountMenu .menuHeader .muted {white-space:nowrap; overflow:hidden; text-overflow:ellipsis;}

	#AccountMenu .menuHeader .visibilityForm
	{
		margin-top: 10px;
		color: #176093;
	}
	
	#AccountMenu .menuHeader .links .fl
	{
		position: absolute;
		bottom: 10px;
		left: 116px;
	}

	#AccountMenu .menuHeader .links .fr
	{
		position: absolute;
		bottom: 10px;
		right: 10px;
	}
	
#AccountMenu .menuColumns
{
	overflow: hidden; zoom: 1;
	padding: 2px;
}

	#AccountMenu .menuColumns ul
	{
		float: left;
		padding: 0;
		max-height: none;
		overflow: hidden;
	}

		#AccountMenu .menuColumns a,
		#AccountMenu .menuColumns label
		{
			width: 115px;
		}

#AccountMenu .statusPoster textarea
{
	width: 245px;
	margin: 0;
	resize: vertical;
	overflow: hidden;
}

#AccountMenu .statusPoster .submitUnit
{
	margin-top: 5px;
	text-align: right;
}

	#AccountMenu .statusPoster .submitUnit .statusEditorCounter
	{
		float: left;
		line-height: 23px;
		height: 23px;
	}
	
/* ---------------------------------------- */
/* Inbox, Alerts Popups */

.navPopup
{
	width: 260px;
}

.navPopup a:hover,
.navPopup .listItemText a:hover
{
	background: none;
	text-decoration: underline;
}

	.navPopup .menuHeader .InProgress
	{
		float: right;
		display: block;
		width: 20px;
		height: 20px;
	}

.navPopup .listPlaceholder
{
	max-height: 350px;
	overflow: auto;
}

	.navPopup .listPlaceholder ol.secondaryContent
	{
		padding: 0 10px;
	}

		.navPopup .listPlaceholder ol.secondaryContent.Unread
		{
			background-color: #F0F7FC;
		}

.navPopup .listItem
{
	overflow: hidden; zoom: 1;
	padding: 5px 0;
	border-bottom: 1px solid #D7EDFC;
}

.navPopup .listItem:last-child
{
	border-bottom: none;
}

.navPopup .PopupItemLinkActive:hover
{
	margin: 0 -8px;
	padding: 5px 8px;
	border-radius: 5px;
	background-color: #D7EDFC;
	cursor: pointer;
}

.navPopup .avatar
{
	float: left;
}

	.navPopup .avatar img
	{
		width: 32px;
		height: 32px;
	}

.navPopup .listItemText
{
	margin-left: 37px;
}

	.navPopup .listItemText .muted
	{
		font-size: 9px;
	}

	.navPopup .unread .listItemText .title,
	.navPopup .listItemText .subject
	{
		font-weight: bold;
	}

.navPopup .sectionFooter .floatLink
{
	float: right;
}


@media (max-width:610px)
{
	.Responsive .navTabs
	{
		padding-left: 10px;
		padding-right: 10px;
	}

	.Responsive .withSearch .navTabs .navTab.selected .blockLinksList
	{
		margin-right: 50px;
	}
}

@media (max-width:480px)
{
	.Responsive.hasJs .navTabs:not(.showAll) .publicTabs .navTab:not(.selected):not(.navigationHiddenTabs)
	{
		display: none;
	}
}



/* flashing alert */
@keyframes alert-flash {
  0% {background-color:#E03030; -webkit-transform: scale(1); -ms-transform: scale(1);transform:scale(1);}
  5% {background-color:#FFFFFF; -webkit-transform: scale(1.1); -ms-transform: scale(1.1);transform:scale(1.1);}
  15% {-webkit-transform: scale(1); -ms-transform: scale(1);transform:scale(1);}
  25% {background-color:#E03030;}
/*50% {-webkit-transform: scale(1); -ms-transform: scale(1);transform:scale(1);}
  55% {-webkit-transform: scale(1.1); -ms-transform: scale(1.1);transform:scale(1.1);}
  65% {-webkit-transform: scale(1); -ms-transform: scale(1);transform:scale(1);} */
}
@keyframes alert-arrow {
  0% {border-top-color:#E03030; -webkit-transform: scale(1); -ms-transform: scale(1);transform:scale(1);}
  5% {border-top-color:#FFFFFF; -webkit-transform: scale(1.1); -ms-transform: scale(1.1);transform:scale(1.1);}
  15% {-webkit-transform: scale(1); -ms-transform: scale(1);transform:scale(1);}
  25% {border-top-color:#E03030;}
/*50% {-webkit-transform: scale(1); -ms-transform: scale(1);transform:scale(1);}
  55% {-webkit-transform: scale(1.1); -ms-transform: scale(1.1);transform:scale(1.1);}
  65% {-webkit-transform: scale(1); -ms-transform: scale(1);transform:scale(1);} */
}
.navTabs .navLink .itemCount {animation:alert-flash 3s ease-in 2s infinite;}
.navTabs .navLink .itemCount .arrow {animation:alert-arrow 3s ease-in 2s infinite;}


#searchBar
{
	position: relative;
	zoom: 1;
	z-index: 52; /* higher than breadcrumb arrows */
}

	#QuickSearchPlaceholder
	{
		position: absolute;
		right: 20px;
		top: -27px;
		display: none;
		border-radius: 5px;
		cursor: pointer;
		font-size: 11px;
		height: 16px;
		width: 16px;
		box-sizing: border-box;
		text-indent: -9999px;
		background: transparent url('styles/default/xenforo/xenforo-ui-sprite.png') no-repeat -144px 0px;
		overflow: hidden;
	}

	#QuickSearch
	{
		display: block;
		position: absolute;
		right: 30px;
		top: -43px;
		padding:6px 5px;
		margin: 0;
		border:1px solid transparent; 
		border-radius:0;
		background-color:#E5EFF9;
		border-radius: 5px;
		z-index: 7500;
		background:transparent;
	}
			
		#QuickSearch .secondaryControls
		{
			display: none;
		}
	
		#QuickSearch.active
		{
			padding-bottom:5px;
			border-color:#CFE3F1;
			background-color:#FFFFFF;
			background-image:linear-gradient(#E5EFF9,#FFFFFF);
			box-shadow:5px 5px 25px rgba(0,0,0,0.5);
		}
		
	#QuickSearch .submitUnit .button
	{
		min-width: 0;
	}
		
	#QuickSearch input.button.primary
	{
		float: left;
		width: 110px;
	}
	
	#QuickSearch #commonSearches
	{
		float: right;
	}
	
		#QuickSearch #commonSearches .button
		{
			width: 23px;
			padding: 0;
		}
		
			#QuickSearch #commonSearches .arrowWidget
			{
				margin: 0;
				float: left;
				margin-left: 4px;
				margin-top: 4px;
			}
	
	#QuickSearch .moreOptions
	{
		display: block;
		margin: 0 24px 0 110px;
		width: auto;
	}


@media (max-width:610px)
{
	.Responsive #QuickSearchPlaceholder
	{
		display: block;
	}

	.Responsive #QuickSearchPlaceholder.hide
	{
		visibility: hidden;
	}

	.Responsive #QuickSearch
	{
		display: none;
	}

	.Responsive #QuickSearch.show
	{
		display: block;
	}
}


/** move the header to the top again **/

#headerMover
{
	position: relative;
	zoom: 1;
}

	#headerMover #headerProxy
	{
		background-color: #1B1F20;
		height: 159px; /* +2 borders */
	}

	#headerMover #header
	{
		width: 100%;
		position: absolute;
		top: 0px;
		left: 0px;
	}


/** Generic page containers **/

.pageWidth
{
	box-sizing:border-box; margin:0 auto; padding:0 15px; max-width:1340px;

}

.NoResponsive body
{
	min-width: 976px;
}

#content .pageContent
{
	background-color: #E5EFF9;
padding: 0 20px;

}

/* clearfix */ #content .pageContent { zoom: 1; } #content .pageContent:after { content: '.'; display: block; height: 0; clear: both; visibility: hidden; }

/* sidebar structural elements */

.mainContainer
{
	 float: left;
	 margin-right: -260px;
	 width: 100%;
}

	.mainContent
	{
		margin-right: 260px;
	}

.sidebar
{
	float: right;
	font-size: 12px;
width: 250px;

}







/* visitor panel */

.sidebar .visitorPanel
{
	overflow: hidden; zoom: 1;
}

	.sidebar .visitorPanel h2 .muted
	{
		display: none;
	}

	.sidebar .visitorPanel .avatar
	{
		margin-right: 8px;
float: left;

		
		width: auto;
		height: auto;
	}
	
		.sidebar .visitorPanel .avatar img
		{
			width: ;
			height: ;
		}
	
	.sidebar .visitorPanel .username
	{
		font-weight: bold;
font-size: 15px;

	}
	
	.sidebar .visitorPanel .stats
	{
		margin-top: 2px;

	}
	
	.sidebar .visitorPanel .stats .pairsJustified
	{
		line-height: normal;
	}













	
/* generic sidebar blocks */
		
.sidebar .section .primaryContent h3,
.sidebar .section .secondaryContent h3,
.profilePage .mast .section.infoBlock h3
{
	font-size: 14px;
color: #FFF;
background-color: #141414;
padding: 11px 10px;
background-image: linear-gradient(#3E3E3E,#000000);
/*margin: -10px -10px 10px;*/

}

.sidebar .section .primaryContent h3 a,
.sidebar .section .secondaryContent h3 a
{
	font-size: 14px;
color: #FFF;
}

.sidebar .section .secondaryContent .footnote,
.sidebar .section .secondaryContent .minorHeading
{
	color: #646464;
margin-top: 5px;

}

	.sidebar .section .secondaryContent .minorHeading a
	{
		color: #646464;
	}












/* list of users with 32px avatars, username and user title */

.sidebar .avatarList li
{
	padding-top: 5px;
margin: 5px 0;
border-top: 1px solid #D7EDFC;
overflow: hidden;
zoom: 1;

}
.sidebar .avatarList li:first-of-type {padding-top:0; border-top:0;}


	.sidebar .avatarList .avatar
	{
		margin-right: 5px;
float: left;
width: 32px;
height: 32px;

		
		width: auto;
		height: auto;
	}
		
	.sidebar .avatarList .avatar img
	{
		width: 32px;
		height: 32px;
	}
	
	.sidebar .avatarList .username
	{
		font-size: 15px;
margin-top: 2px;
display: block;

	}
	
	.sidebar .avatarList .userTitle
	{
		color: #969696;

	}









/* list of users */

.sidebar .userList
{
}

	.sidebar .userList .username
	{
		font-size: 11px;

	}

	.sidebar .userList .username.invisible
	{
		color: #65A5D1;

	}
	
	.sidebar .userList .username.followed
	{
		
	}

	.sidebar .userList .moreLink
	{
		display: block;
	}
	
	
	
	
/* people you follow online now */

.followedOnline
{
	margin-top: 3px;
margin-bottom: -5px;
overflow: hidden;
zoom: 1;

}

.followedOnline li
{
	margin-right: 5px;
margin-bottom: 5px;
float: left;

}

	.followedOnline .avatar
	{
		width: 32px;
height: 32px;

		
		width: auto;
		height: auto;
	}
	
		.followedOnline .avatar img
		{
			width: 32px;
			height: 32px;
		}
	
	
	

	
	
/* call to action */

#SignupButton
{
	margin: 10px 30px;
display: block;
text-align: center;
line-height: 30px;
box-shadow: 0 2px 5px rgba(0,0,0,0.2);
cursor: pointer;
height: 30px;

}

	#SignupButton .inner
	{
		font-weight: bold;
font-size: 16px;
font-family: Tahoma,Roboto,Arial,sans-serif;
color: #FFFFFF;
background-color: #000000;
border-radius: 3px;
display: block;

	}
	
	#SignupButton:hover .inner
	{
		text-decoration: none;
background-color: #176093;

	}
	
	#SignupButton:active
	{
		box-shadow: 0 0 3px rgba(0,0,0, 0.2);
/*position: relative;
		top: 2px;*/

	}


@media (max-width:800px)
{
	.Responsive .mainContainer
	{
		 float: none;
		 margin-right: 0;
		 width: auto;
	}

		.Responsive .mainContent
		{
			margin-right: 0;
		}
	
	.Responsive .sidebar
	{
		float: none;
		margin: 0 auto;
	}

		.Responsive .sidebar .visitorPanel
		{
			display: none;
		}
}

@media (max-width:340px)
{
	.Responsive .sidebar
	{
		width: 100%;
	}
}


/** Text used in message bodies **/

.messageText
{
	font-size: 16px;
font-family: Roboto,"Segoe UI",Arial,sans-serif;
line-height: 1.4;

}

	.messageText img,
	.messageText iframe,
	.messageText object,
	.messageText embed
	{
		max-width: 100%;
	}

/** Link groups and pagenav container **/

.pageNavLinkGroup
{
	display: table;
	*zoom: 1;
	table-layout: fixed;
	box-sizing: border-box;
	
	font-size: 11px;
color: #65A5D1;
background-color: #000000;
margin: 0;

}

opera:-o-prefocus, .pageNavLinkGroup
{
	display: block;
	overflow: hidden;
}

	.pageNavLinkGroup:after
	{
		content: ". .";
		display: block;
		word-spacing: 99in;
		overflow: hidden;
		height: 0;
		font-size: 0.13em;
		line-height: 0;
	}

	.pageNavLinkGroup .linkGroup
	{
		float: right;
	}

.linkGroup
{
}
	
	.linkGroup a
	{
		color: #D7EDFC;
background-color: #2B485C;
border-radius: 3px;

	}

		.linkGroup a.inline
		{
			padding: 0;
		}

	.linkGroup a,
	.linkGroup .Popup,
	.linkGroup .element
	{
		margin-left: 10px;
		display: block;
		float: left;
		
	}
	
		.linkGroup .Popup a
		{
			margin-left: -2px;
			margin-right: -5px;
			*margin-left: 10px;
			padding:  5px;
		}

	.linkGroup .element
	{
		padding: 3px 0;
	}

/** Call to action buttons **/

a.callToAction
{
	background-color: #176093;
padding: 10px 15px;
margin-bottom: 10px;
border-radius: 6px;
display: inline-block;
line-height: 18px;
box-shadow: 1px 1px 5px rgba(0,0,0,0.15);
outline: 0 none;
vertical-align: top;
height: 18px;

	
}

	a.callToAction span
	{
		font-weight: bold;
font-size: 11px;
font-family: Tahoma,Roboto,Arial,sans-serif;
color: #FFFFFF;
border-radius: 3px;
display: block;
/*text-shadow: 0px 0px 3px #176093;*/

	}
	
	a.callToAction:hover
	{
		text-decoration: none;
	}

		a.callToAction:hover span
		{
			background-color: #FFDD44;

		}
		
		a.callToAction:active
		{
			/*position: relative;
			top: 2px;*/
		}
		
		a.callToAction:active span
		{
			
		}

/*********/

.avatarHeap
{
	overflow: hidden; zoom: 1;
}

	.avatarHeap ol
	{
		margin-right: -4px;
		margin-top: -4px;
	}
	
		.avatarHeap li
		{
			float: left;
			margin-right: 4px;
			margin-top: 4px;
		}
		
		.avatarHeap li .avatar
		{
			display: block;
		}
		
/*********/

.fbWidgetBlock .fb_iframe_widget,
.fbWidgetBlock .fb_iframe_widget > span,
.fbWidgetBlock .fb_iframe_widget iframe
{
	width: 100% !important;
}

/*********/

.tagBlock
{
	margin: 10px 0;
	font-size: 11px;
}

.tagList,
.tagList li
{
	display: inline;
}


.tagList .tag
{
	position: relative;
	display: inline-block;
	background: #F0F7FC;
	margin-left: 9px;
	height: 14px;
	line-height: 14px;
	padding: 1px 4px 1px 6px;
	border: 1px solid #CFE3F1;
	border-left: none;
	border-radius: 4px;
	border-top-left-radius: 0;
	border-bottom-left-radius: 0;
	color: #176093;
	font-size: 11px;
	margin-bottom: 2px;
}

	.tagList .tag:hover
	{
		text-decoration: none;
		background-color: #D7EDFC;
	}

	.tagList .tag .arrow
	{
		position: absolute;
		display: block;
		height: 2px;
		width: 0;
		left: -9px;
		top: -1px;
		border-style: solid;
		border-width: 8px 9px 8px 0;
		border-color: transparent;
		border-right-color: #CFE3F1;
	}

		.tagList .tag .arrow:after
		{
			content: '';
			position: absolute;
			display: block;
			height: 2px;
			width: 0;
			left: 1px;
			top: -7px;
			border-style: solid;
			border-width: 7px 8px 7px 0;
			border-color: transparent;
			border-right-color: #F0F7FC;
		}

		.tagList .tag:hover .arrow:after
		{
			border-right-color: #D7EDFC;
		}

	.tagList .tag:after
	{
		content: '';
		position: absolute;
		left: -2px;
		top: 6px;
		display: block;
		height: 3px;
		width: 3px;
		border-radius: 50%;
		border: 1px solid #CFE3F1;
		background: #FCFCFF;
	}

/* User name classes */


.username .banned
{
	text-decoration: line-through;
}

.prefix
{
	background-color: transparent;
padding: 0 6px;
margin: -1px 0;
border: 1px solid transparent;
display: inline-block;
background-image: linear-gradient(transparent,#FFFFFF);

}

a.prefixLink:hover
{
	text-decoration: none;
}

a.prefixLink:hover .prefix
{
	color: #176093;
text-decoration: none;
background-color: #F0F7FC;
padding: 0 6px;
border: 1px solid #CFE3F1;

}
a.prefixLink:hover .prefix.prefixOrange {background-color:#FA0;}

.prefix a { color:inherit; }

.prefix.prefixPrimary    { color: #176093; background-color: #CFE3F1; border-color: #CFE3F1; }
.prefix.prefixSecondary  { color: #444444; background-color: #E5EFF9; border-color: #E5EFF9; }

.prefix.prefixRed        { color: #FFFFFF; background-color: #FF0000; border-color: #FF8888; }
.prefix.prefixGreen      { color: #FFFFFF; background-color: #008000; border-color: #008000; }
.prefix.prefixOlive      { color: #000000; background-color: #808000; border-color: #808000; }
.prefix.prefixLightGreen { color: #000000; background-color: #90EE90; border-color: #90EE90; }
.prefix.prefixBlue       { color: #FFFFFF; background-color: #0000FF; border-color: #8888FF; }
.prefix.prefixRoyalBlue  { color: #FFFFFF; background-color: #4169E1; border-color: #81A9E1; }
.prefix.prefixSkyBlue    { color: #000000; background-color: #87CEEB; border-color: #87CEEB; }
.prefix.prefixGray       { color: #000000; background-color: #808080; border-color: #AAAAAA; }
.prefix.prefixSilver     { color: #000000; background-color: #C0C0C0; border-color: #C0C0C0; }
.prefix.prefixYellow     { color: #000000; background-color: #FFFF00; border-color: #E0E000; }
.prefix.prefixOrange     { color: #000000; background-color: #FFA500; border-color: #FFC520; }

.discussionListItem .prefix,
.searchResult .prefix
{
	font-size: 80%;
margin: 0;
line-height: 16px;

	font-weight: normal;
}

h1 .prefix
{
	font-size: 80%;
margin: 0;
line-height: 16px;

	
	line-height: normal;
}

.breadcrumb span.prefix,
.heading span.prefix
{
	font-style: italic;
font-weight: bold;
padding: 0;
margin: 0;
border: 0 none black;
border-radius: 0;
display: inline;

	color: inherit;
}

.userBanner
{
	font-size: 11px;
	background-color:transparent;
	background-image:linear-gradient(#FFFFFF,transparent);
	padding: 1px 5px;
	border: 1px solid transparent;
	border-radius: 3px;
	box-shadow: 1px 1px 3px rgba(0,0,0,0.25);
	text-align: center;
}

	.userBanner.wrapped
	{
		border-top-right-radius: 0;
		border-top-left-radius: 0;
		position: relative;
	}
		
		.userBanner.wrapped span
		{
			position: absolute;
			top: -4px;
			width: 5px;
			height: 4px;
			background-color: inherit;
		}
		
		.userBanner.wrapped span.before
		{
			border-top-left-radius: 3px;
			left: -1px;
		}
		
		.userBanner.wrapped span.after
		{
			border-top-right-radius: 3px;
			right: -1px;
		}

.userBanner.bannerStaff { color: #176093; background-color: #D7EDFC; border-color: #CFE3F1; }
.userBanner.bannerStaff.wrapped span { background-color: #CFE3F1; }

.userBanner.bannerPrimary { color: #176093; background-color: #D7EDFC; border-color: #CFE3F1; }
.userBanner.bannerPrimary.wrapped span { background-color: #CFE3F1; }

.userBanner.bannerSecondary { color: #444444; background-color: #E5EFF9; border-color: #E5EFF9; }
.userBanner.bannerSecondary.wrapped span { background-color: #E5EFF9; }

.userBanner.bannerRed        { color: white; background-color: red; border-color: #F88; }
.userBanner.bannerRed.wrapped span { background-color: #F88; }

.userBanner.bannerGreen      { color: white; background-color: green; border-color: green; }
.userBanner.bannerGreen.wrapped span { background-color: green; }

.userBanner.bannerOlive      { color: black; background-color: olive; border-color: olive; }
.userBanner.bannerOlive.wrapped span { background-color: olive; }

.userBanner.bannerLightGreen { color: black; background-color: lightgreen; border-color: lightgreen; }
.userBanner.bannerLightGreen.wrapped span { background-color: lightgreen; }

.userBanner.bannerBlue       { color: white; background-color: blue; border-color: #88F; }
.userBanner.bannerBlue.wrapped span { background-color: #88F; }

.userBanner.bannerRoyalBlue  { color: white; background-color: royalblue; border-color: #81A9E1;  }
.userBanner.bannerRoyalBlue.wrapped span { background-color: #81A9E1; }

.userBanner.bannerSkyBlue    { color: black; background-color: skyblue; border-color: skyblue; }
.userBanner.bannerSkyBlue.wrapped span { background-color: skyblue; }

.userBanner.bannerGray       { color: black; background-color: gray; border-color: #AAA; }
.userBanner.bannerGray.wrapped span { background-color: #AAA; }

.userBanner.bannerSilver     { color: black; background-color: silver; border-color: silver; }
.userBanner.bannerSilver.wrapped span { background-color: silver; }

.userBanner.bannerYellow     { color: black; background-color: yellow; border-color: #E0E000; }
.userBanner.bannerYellow.wrapped span { background-color: #E0E000; }

.userBanner.bannerOrange     { color: black; background-color: orange; border-color: #FFC520; }
.userBanner.bannerOrange.wrapped span { background-color: #FFC520; }

.userBanner.bannerHidden.wrapped { margin-left: 0; margin-right: 0; }
.userBanner.bannerHidden.wrapped span { display: none; }
.userBanner.bannerStaff.wrapped span {background-color:transparent;}

.userBanner.bannerHidden,
.userBanner.bannerStaff {padding:0; border:0; border-radius:0; font-size:0; background:none; box-shadow:none;}

/* Change User Banner Staff */
.userBanner.bannerStaff strong {
display:inline-block;
width:163px;
height:30px;
background-image:url('/data/attachments/usertitles/fb-staff.png');
background-color:transparent;
border:0;
border-radius:0;
box-shadow:none;
color:transparent;
font-size:0;
}

.bottomFixer
{
	position: fixed;
	left: 0;
	right: 0;
	bottom: 0;
	z-index: 800;
	pointer-events: none;
}

.bottomFixer > *
{
	pointer-events: auto;
}


@media (max-width:800px)
{
	.Responsive .pageWidth
	{
		
	}

	.Responsive #content .pageContent
	{
		padding-left: 10px;
		padding-right: 10px;
	}
}

@media (max-width:610px)
{
	.Responsive .pageWidth
	{
		padding-right: 0;
padding-left: 0;
margin-right: 0;
margin-left: 0;

	}
	
	.Responsive .forum_view #pageDescription,
	.Responsive .thread_view #pageDescription
	{
		display: none;
	}
}

@media (max-width:480px)
{
	.Responsive .pageWidth
	{
		
	}
	
	.Responsive .pageNavLinkGroup .PageNav,
	.Responsive .pageNavLinkGroup .linkGroup
	{
		clear: right;
	}
}


/* EXTRA.CSS */

/* Fonts */

@import url('https://fonts.googleapis.com/css?family=Oswald|Roboto');


/* Basic Page Elements */

.breadcrumb .boardTitle {display:none;}
.breadcrumb .crust .arrow {display:none;}
/*.breadcrumb .crust .arrow span {}*/
.breadcrumb .crust:before {content:"▶"; display:block; float:left; color:#646464; font-size:0.8em; line-height:24px; padding-left:1px;}
.breadcrumb .crust.homeCrumb:before {display:none;}

/* why oh why is there home->forums anyway */
.breadcrumb .crust.homeCrumb {display:none!important;}
.breadcrumb .crust:nth-of-type(2):before {display:none;}
.breadcrumb .crust:nth-of-type(2) a.crumb {padding-left:0;}

/*
#content.error .breadBoxTop, #content.error .breadBoxBottom,
#content.report_list .breadBoxTop, #content.report_list .breadBoxBottom,
#content.message_page .breadBoxTop, #content.message_page .breadBoxBottom,
#content.register_form .breadBoxTop, #content.register_form .breadBoxBottom,
#content.register_process .breadBoxTop, #content.register_process .breadBoxBottom,
#content.search_results_users_only .breadBoxTop, #content.search_results_users_only .breadBoxBottom {display:none;}
#content.error .pageContent,
#content.report_list .pageContent,
#content.message_page .pageContent,
#content.register_form .pageContent,
#content.register_process .pageContent,
#content.search_results_users_only .pageContent {padding:20px;}
*/
#content.error fieldset.breadcrumb,
#content.report_list fieldset.breadcrumb,
#content.message_page fieldset.breadcrumb,
#content.register_form fieldset.breadcrumb,
#content.register_process fieldset.breadcrumb,
#content.search_results_users_only fieldset.breadcrumb {display:none;}


#QuickSearch .controlsWrapper {background:#FFFFFF; border-radius:0;}
#QuickSearch .formPopup {background:transparent!important;}
#QuickSearch .formPopup .primaryControls {padding:2px 5px 5px;}
#QuickSearch input.button.primary {width:108px;}
#QuickSearch .moreOptions {margin-left:109px;}
#QuickSearch #commonSearches a {background:transparent;}
#QuickSearch #commonSearches .arrowWidget {margin:10px 0 0 5px;}

.container {margin:10px 0;}

.mainContent {margin-right:270px;}

.titleBar {margin:0;}
.titleBar p {display:none;}

.button.spinBoxButton {font-size:inherit; font-weight:bold; font-family:Verdana,Tahoma,"Segoe UI",sans-serif;}

.callToAction:hover, .pageNavLinkGroup .linkGroup .callToAction:hover, a.callToAction:hover span {background:#65A5D1; color:#FFFFFF;}
.topCtrl .callToAction {margin:0; padding:3px 10px; min-width:50px; text-align:center;}

.sharePage {margin-top:20px;}
.sharePage h3 {display:none;}

.pageNavLinkGroup {width:100%;} .pageNavLinkGroup:after {display:none;} /* fix for asinine margin underneath page nav */
.pageNavLinkGroup {background:#222;}
/*.pageNavLinkGroup .PageNav {padding:6px 0;}
.conversation_list .PageNav, .conversation_list_yours .PageNav {padding:6px 10px; background:#222;}*/
.PageNav {padding:6px 10px; background:#222;}
.tagBlock {margin:0; padding-bottom:10px; color:#555;}

.PageNav .pageNavHeader {margin-right:10px; padding:0;}
.PageNav .pageNavHeader, .PageNav a, .PageNav .scrollable, .pageNavLinkGroup .linkGroup>* {height:28px!important; line-height:28px; margin-bottom:0;}
.PageNav nav a {padding:0 1px; background:#444; color:#FFF; border-radius:2px; font-size:11px; font-family:Roboto,"Segoe UI",Tahoma,Arial,sans-serif; font-weight:bold;}
.PageNav nav span.scrollable {width:12em; height:1.5em;}
.pageNavLinkGroup a.unreadLink {padding:0 1em; border-radius:3px;}
/*.pageNavLinkGroup .linkGroup .element {padding:0;}*/
.pageNavLinkGroup .linkGroup a {padding:0 1em; margin:6px 10px 6px 0;}
.pageNavLinkGroup .linkGroup a:hover {background:#176093; color:#FFF;}
.pageNavLinkGroup .Popup .PopupControl {padding:0 10px;}
.pageNavLinkGroup.afterDiscussionListHandle {margin-top:0;}


/* Forums on Site (Top Page) */

.forum_list .titleBar {display:none;}

#forums .nodeList>.node:nth-of-type(even)>*,
.discussionListItems .discussionListItem:nth-of-type(even) {background:#F0F7FC;} /* alternating off-white forum/thread lists */

.lastThreadMeta .lastThreadDate {color:#444444;}

.pageContent .discussionList .sectionHeaders a span {padding:8px 10px;}

#userList {margin-top:20px;}
#userList .categoryStrip {background:#F0F7FC; color:#646464; font-size:13px;}
#userList .categoryStrip .title {margin-right:1em; font-size:1.17em;}
#userList .categoryStrip .stats {color:#969696;}
#userList .listInline {background:#FCFCFF; padding:10px; font-size:11px;}

/* Forums sidebar */
.sidebar .section {margin:20px 0;}
/*.sidebar .section:first-of-type {margin-top:10px;}*/
.sidebar .visitorPanel {background:transparent;}
.sidebar .visitorPanel .secondaryContent {min-height:100px;}
.sidebar .secondaryContent h3 {margin:-10px -10px 10px;}
#boardStats .pairsJustified dt {color:#444; font-weight:bold;}
@media (max-width:480px) { .Responsive .sidebar {width:100%;} }


/* Threads in Forum */

.thread_view form.section {margin:0;}

.container .navigationSideBar {width:170px; padding-right:20px;}
.container .navigationSideBar .heading {margin:0;}
.container .navigationSideBar .section {margin-bottom:20px;}

.discussionListItem .lastPost .lastPostInfo {padding:5px 8px;}
.discussionListItem .lastPost .dateTime {font-family:Tahoma,"Segoe UI",Arial,sans-serif;}


.discussionListItem .iconKey span {margin-left:5px;}

@media screen and (max-width:479px) { .discussionListItem .iconKey {width:100%;} }
.discussionListItem .iconKey {display:inline-block; float:right;}
.discussionListItem .iconKey span {display:inline-block; float:right; color:#555; font-size:0; font-weight:bold;}
.discussionListItem .iconKey span.sticky {color:#65A5D1; font-size:11px;}
.discussionListItem .iconKey span.moderated {color:#C03; font-size:11px;}


.discussionList .discussionListItem.sticky {background-color:#D7EDFC!important;background-image:linear-gradient(rgba(255,255,255,0.2),rgba(0,0,0,0))!important}

.discussionList .discussionListItem.moderated,
.discussionList .discussionListItem.moderated {background:url(rgba.php?r=255&g=0&b=0&a=51)!important; background:rgba(255,0,0,0.2)!important; _filter: progid:DXImageTransform.Microsoft.gradient(startColorstr=#33FF0000,endColorstr=#33FF0000); border-color:#C66; border-top:1px solid #C66; margin-top:-1px;}
.discussionList .discussionListItem.moderated .listBlock a {color:#C03;}
.discussionList .discussionListItem.moderated .listBlock a:hover {color:#C03;}
.discussionList .discussionListItem.moderated .listBlock dl {border-color: rgb(204,0,0); border-color: rgba(204,0,0, 0.4); _border-color: rgb(204,0,0);}

.discussionList .discussionListItem.deleted {background:#FCFCFF!important;}
.discussionList .discussionListItem.deleted label,
.discussionList .discussionListItem.deleted .deletionNote {color:#C8C8C8!important;}
.discussionList .discussionListItem.deleted .username .banned {color:#AAA; font-weight:bold;}
.discussionList .discussionListItem.deleted .username:hover .banned {text-decoration:none;}

.discussionList .discussionListItem .posterAvatar,
.discussionList .discussionListItem.sticky .listBlock,
.discussionList .discussionListItem.moderated .listBlock,
.discussionList .discussionListItem.deleted .listBlock {background:transparent!important;}


/* Messages in Thread */

/*.user_banner {width:auto; height:auto;}*/

.messageUserBlock div.avatarHolder .avatar,
.messageUserBlock .avatar img {background:#FCFCFF;}
.messageUserBlock .avatar img {border-radius:4px;}

.messageUserInfo .userText>* {text-align:center;}
.messageUserInfo .userText .username {font-size:18px; line-height:24px; font-family:Roboto,"Segoe UI",Tahoma,Arial,sans-serif;}

.messageUserInfo .userText,
.messageUserInfo .extraUserInfo .medals {border:1px solid #D6E0EA; background:url(rgba.php?r=255&g=255&b=255&a=25); background:rgba(255,255,255,0.1); _filter: progid:DXImageTransform.Microsoft.gradient(startColorstr=#19FFFFFF,endColorstr=#19FFFFFF);}

.messageUserInfo .extraUserInfo .medals {display:flex; flex-direction:row; flex-wrap:wrap; justify-content:space-around; align-content:flex-start; overflow:hidden; box-sizing:border-box; width:184px; max-height:100px; margin:0; padding:3px 4px;}
.messageUserInfo .extraUserInfo .medals a {align-self:center; line-height:0; margin:auto; padding:3px 0;}

.ugc a:hover, .ugc a:focus {box-shadow:none;}

.messageInfo .messageTop {margin-bottom:0.5em;}
.messageInfo .messageTop .DateTime {color:#969696; font-family:Verdana,"Segoe UI",Arial,sans-serif; font-size:11px; line-height:1;}

.messageNotices li.moderatedNotice {background-color:#F99; background-image:linear-gradient(#FCC,#F77); border:1px solid #C00; color:#000;}
/*.messageNotices ~ .messageContent {background:#FCC!important;padding:10px;}*/

.InlineModChecked .messageUserInfo .userText, .InlineModChecked .messageUserInfo .extraUserInfo .medals {border:1px solid #E5EFF9;}

/* Subpages */

.insideSidebar {padding:10px 12px;}
.insideSidebar * {font-family:Verdana,Arial,sans-serif!important; font-style:normal!important;}

.profilePage {background:#FCFCFF; margin-bottom:10px;}
.profilePage .primaryUserBlock {margin:0;}
.profilePage .primaryUserBlock .tabs.mainTabs {background:transparent;}
.profilePage .primaryUserBlock .tabs.mainTabs li a:hover {background:#E5EFF9; color:#000000;}
.profilePage .mast {background:#E5EFF9;}
.profilePage .mast .avatarScaler {background:transparent; /*padding:6px 0 3px; border:1px solid #FFF; text-align:center;*/}
.profilePage .mast .avatarScaler img {display:block;}
.profilePage .profileContent {padding-right:20px;}
.profilePage #ProfilePanes {margin-top:1em;}

#ProfilePostList .messageSimple .messageMeta {max-width:450px;}
#ProfilePostList blockquote * {font-weight:normal; text-decoration:none!important;}
#ProfilePostList blockquote iframe,
#ProfilePostList blockquote>div {display:block!important; margin:5px 0 10px;}
/*#ProfilePostList blockquote div[data-s9e-mediaembed="youtube"],
#ProfilePostList blockquote div[data-s9e-mediaembed="twitch"],
#ProfilePostList blockquote div[data-s9e-mediaembed="googledrive"]*/

/*.messageUserBlock .extraUserInfo {height:0; padding:0 4px; transition:all ease-out 0.5s;}
.messageUserBlock .extraUserInfo dl {display:none;}
.messageUserBlock:hover .extraUserInfo {height:auto; padding:4px}
.messageUserBlock:hover .extraUserInfo dl {display:inline-block;}*/

/*.discussionListItem .itemPageNav a {background:#444; color:#FFF; border:0;}
.discussionListItem .itemPageNav a:hover {background:#E5EFF9; color:#444; border:0;}*/

@media (max-width:480px) {
.container .navigationSideBar {padding-right:0;}
.Responsive .container .navigationSideBar {width:100%;}
}


/* Blog */

/*.messageInfo:not(:first-of-type) .privateControls a {background:#000000; color:#FFFFFF; padding:0.5em 1em; border-radius:3px;}
.messageInfo:not(:first-of-type) .privateControls a:hover {background:#176093; color:#FFFFFF;}*/

.blogList .blogEntry {margin:0 auto;}
.blogList .blogEntry .messageContent {padding:1em;}

.blogCommentList .messageSimpleList>li {padding:0 10px 10px;}

.CommentForm .submitRow {margin-bottom:10px;}

.online_list .tabs,
.member_notable .tabs,
.find_new_posts .tabs,
.find_new_profile_posts .tabs,
.find_new_blogs .tabs,
.th_find_new_blogs_none .tabs {padding-top:10px;}

/*.online_list .memberList,
.member_notable .memberList,
.find_new_posts .section*/
.tabs + .section {margin-top:0; padding:10px 12px;}
.tabs + .section.memberList {padding:0;}

.th_find_new_blogs_none .section,
.find_new_profile_posts .section {margin:0 auto; padding:10px;}

/*.newsFeed .event {background:#F0F4FC;}*/


/* Help */

.help_cookies .baseHtml, .help_terms .baseHtml, .help_page .baseHtml {padding:10px;}


/* Forms */

/* User Registration and Login */
.xenForm.AutoValidator, .xenForm#pageLogin, .xenForm[action$=warn] {max-width:none; margin:0 auto; padding:10px 0; background:#FCFCFF;}
.xenForm.AutoValidator > *, .xenForm#pageLogin > *, .xenForm[action$=warn] > * {max-width:800px; margin-left:auto; margin-right:auto;}
.xenForm.AutoValidator fieldset {background:#F0F7FC; margin:20px auto 0; padding:10px 0;}
.xenForm.AutoValidator fieldset + .ctrlUnit {margin-top:0;}
.xenForm#pageLogin .submitUnit {padding:10px 0 0;}

.xenOverlay .xenForm.AutoValidator {background:url(rgba.php?r=0&g=0&b=0&a=178); background:rgba(0,0,0,0.7); _filter: progid:DXImageTransform.Microsoft.gradient(startColorstr=#B2000000,endColorstr=#B2000000);}
.xenOverlay .xenForm.AutoValidator fieldset {background:inherit;}

/* bigger code overlay */
#redactor_modal {max-width:1000px; width:100%!important; left:0!important; margin-left:50%!important; -webkit-transform: translateX(-50%); -ms-transform: translateX(-50%);transform:translateX(-50%);}
#redactor_modal .xenForm {max-width:none;}
#redactor_modal .xenForm .ctrlUnit > dt {width:20%; min-width:10em;}
#redactor_modal .xenForm .ctrlUnit > dd {width:80%;}

/* Mod Tools */
.moderation_queue_list .xenForm {max-width:none; margin:0 auto;}
.moderation_queue_list .xenForm>fieldset {background:linear-gradient(#FCFCFF,#F0F7FC); margin:0 auto; padding:0.5em 0;}
.moderation_queue_list .xenForm>fieldset dd textarea {background:#FFF;}
.moderation_queue_list .xenForm .ctrlUnit > dt {width:18%; min-width:10em;}
/* .moderation_queue_list .xenForm .ctrlUnit > dd {} */
.moderation_queue_list .xenForm .modMessage {white-space:pre-line;}
.moderation_queue_list .breadBoxTop nav,
.moderation_queue_list .breadBoxBottom nav {display:none;}

/* #moderatorBar ~ div */ .thread_view .threadAlerts .moderatedAlert {color:#C03;}

.xenForm.personalDetailsForm fieldset {max-width:none; background:linear-gradient(#FCFCFF,#F0F7FC);}
.xenForm.personalDetailsForm > * {max-width:none;}
.xenForm.personalDetailsForm .ctrlUnit > dt {width:20%;}
.xenForm.personalDetailsForm .ctrlUnit > dd {width:40em; max-width:60%;}
.xenForm.personalDetailsForm .ctrlUnit.OptOut > dd {width:auto; max-width:none;}
.xenForm.personalDetailsForm .submitUnit {padding:10px 0 0;}

.xenForm.Preview {max-width:none; margin:0 auto; padding:10px; background:#FCFCFF;}
.xenForm.Preview fieldset, .xenForm.Preview .textHeading, .xenForm.Preview .ctrlUnit {max-width:1000px;}
.xenForm.Preview .PreviewContainer h3 {background:linear-gradient(#3F3F3F,#000000);}
.xenForm.Preview .PreviewContainer .messageText {background:linear-gradient(#D7EDFC,#FFFFFF);}
.xenForm.Preview .PreviewContainer a {text-decoration:underline;}
.xenForm.Preview .ctrlUnit > dt {width:auto;}

.pageContent > .errorOverlay .baseHtml,
.pageContent > .messageBody {background:#FCFCFF; padding:10px;}


/* hide forum icons entirely
.nodeList .node .nodeIcon {display:none;}
.nodeList .node .nodeText {margin-left:20px;} */

.nodeList .node .forumNodeInfo .nodeIcon,
.node .categoryForumNodeInfo .nodeIcon {/*TEMP*/background-image:url('/data/attachments/thread-icons/winkies/erik_blink.gif');}

/* forum icons */
.node_13 .forumNodeInfo .nodeIcon {background-image:url('');} /* community announcements */
.node_69 .forumNodeInfo .nodeIcon {background-image:url('');} /* product announcements */
.node_74 .forumNodeInfo .nodeIcon {background-image:url('');} /* product discussion */
.node_70 .forumNodeInfo .nodeIcon {background-image:url('');} /* resource staff releases */
.node_14 .forumNodeInfo .nodeIcon {background-image:url('');} /* site feedback */
.node_161 .forumNodeInfo .nodeIcon {background-image:url('');} /* learning together */
.node_155 .forumNodeInfo .nodeIcon {background-image:url('');} /* resurrection jam */
.node_141 .forumNodeInfo .nodeIcon {background-image:url('');} /* maker specific */
.node_50 .forumNodeInfo .nodeIcon {background-image:url('');} /* maker tech support */
.node_123 .forumNodeInfo .nodeIcon {background-image:url('');} /* tutorials */
.node_139 .forumNodeInfo .nodeIcon {background-image:url('');} /* javascript */
.node_138 .forumNodeInfo .nodeIcon {background-image:url('');} /* rgss */
.node_163 .forumNodeInfo .nodeIcon {background-image:url('');} /* vn support */
.node_164 .forumNodeInfo .nodeIcon {background-image:url('');} /* vn tutorials */
.node_165 .forumNodeInfo .nodeIcon {background-image:url('');} /* vn plugins */
.node_19 .forumNodeInfo .nodeIcon {background-image:url('');} /* completed games */
.node_20 .forumNodeInfo .nodeIcon {background-image:url('');} /* project development */
.node_48 .forumNodeInfo .nodeIcon {background-image:url('');} /* early project feedback */
.node_55 .forumNodeInfo .nodeIcon {background-image:url('');} /* classified */
.node_64 .forumNodeInfo .nodeIcon {background-image:url('');} /* commercial rm games */
.node_63 .forumNodeInfo .nodeIcon {background-image:url('');} /* commercial releases */
.node_16 .forumNodeInfo .nodeIcon {background-image:url('');} /* game dev discussion */
.node_17 .forumNodeInfo .nodeIcon {background-image:url('');} /* game mechanics */
.node_28 .forumNodeInfo .nodeIcon {background-image:url('');} /* general resources */
.node_140 .forumNodeInfo .nodeIcon {background-image:url('');} /* maker resources */
.node_49 .forumNodeInfo .nodeIcon {background-image:url('');} /* useful tools */
.node_31 .forumNodeInfo .nodeIcon {background-image:url('');} /* resource requests */
.node_44 .forumNodeInfo .nodeIcon {background-image:url('');} /* hi/bye */
.node_42 .forumNodeInfo .nodeIcon {background-image:url('');} /* lounge */
.node_43 .forumNodeInfo .nodeIcon {background-image:url('');} /* video games */
.node_51 .forumNodeInfo .nodeIcon {background-image:url('');} /* art/lit/music */
.node .forumNodeInfo .nodeIcon {opacity:0.5; background-position:0 0;}
/* .node .forumNodeInfo.unread .nodeIcon {opacity:1;} */

/* Display Page Topic Pages */
.discussionListItem .itemPageNav
{
    visibility: visible !important;
}

#exposeMask {/*transition:opacity ease-out 0.2s;*/}

/* fix for avatars that don't load */
.messageUserBlock .avatar img {display:block;}
.sidebar .avatarList .avatar img {display:inline-block;}

/* Chrome 60+ workaround for poor mods */
#InlineModOverlay {position:fixed!important; top:0!important; left:50%!important; margin-left:-230px!important;}


