@charset "UTF-8";

/* --- bb_code.css --- */

.quoteContainer.expanded iframe[data-s9e-mediaembed],
	.quoteContainer.expanded [data-s9e-mediaembed] iframe
	{
		max-height: none;
		max-width:  none;
	}/* .bbCodeX classes are designed to exist inside .baseHtml. ie: they have no CSS reset applied */

.bbCodeBlock
{
	margin: 1em 200px 1em 0;
border: 1px solid #D7EDFC;
border-radius: 5px;
overflow: auto;

}

	.bbCodeBlock .bbCodeBlock,
	.hasJs .bbCodeBlock .bbCodeSpoilerText,
	.messageList.withSidebar .bbCodeBlock
	{
		margin-right: 0;
	}

	/* mini CSS reset */
	.bbCodeBlock pre,
	.bbCodeBlock blockquote
	{
		margin: 0;
	}
	
	.bbCodeBlock img
	{
		border: none;
	}

.bbCodeBlock .type
{
	font-size: 11px;
font-family: Verdana,"Segoe UI",Arial,Meiryo,sans-serif;
color: #6CB2E4;
background-color: #D7EDFC;
padding: 3px 8px;
border-bottom: 1px solid #CFE3F1;
border-top-left-radius: 4px;
border-top-right-radius: 4px;

}

.bbCodeBlock pre,
.bbCodeBlock .code
{
	font-size: 10pt;
font-family: Consolas,"Courier New",Courier,monospace;
background-color: #F0F7FC;
background-repeat: repeat-x;
background-position: top;
padding: 10px;
border-radius: 5px;
word-wrap: normal;
overflow: auto;
line-height: 1.24;
min-height: 30px;
max-height: 500px;
_width: 600px;
direction: ltr;

}

.bbCodeBlock .code
{
	white-space: nowrap;
}

.bbCodeQuote
{
	border-color: #E5EFF9;
overflow: auto;

}

.bbCodeQuote .attribution
{
	color: #141414;
background-color: #D6E0EA;
border-bottom: 1px solid #E5EFF9;

}

.bbCodeQuote .quoteContainer
{
	overflow: hidden;
	position: relative;
	
	font-style: italic;
font-size: 12px;
background-color: #F0F7FC;
padding: 10px;
border-radius: 4px;

}


	.bbCodeQuote .quoteContainer .quote
	{
		max-height: 150px;
		overflow: hidden;
		padding-bottom: 1px;
	}
	
		.NoJs .bbCodeQuote .quoteContainer .quote
		{
			max-height: none;
		}

	.bbCodeQuote .quoteContainer .quoteExpand
	{		
		display: none;
		box-sizing: border-box;
		position: absolute;
		height: 80px;
		top: 90px;
		left: 0;
		right: 0;
		
		font-size: 13px;
		line-height: 1;
		text-align: center;
		color: #176093;
		cursor: pointer;
		padding-top: 65px;
		background: linear-gradient(to bottom, rgba(240, 247, 252, 0) 0%, #F0F7FC 80%);
		
		border-bottom-left-radius: 4px;
		border-bottom-right-radius: 4px;
	}
	
	.bbCodeQuote .quoteContainer .quoteExpand.quoteCut
	{
		display: block;
	}
	
	.bbCodeQuote .quoteContainer.expanded .quote
	{
		max-height: none;
	}
	
	.bbCodeQuote .quoteContainer.expanded .quoteExpand
	{
		display: none;
	}


	.bbCodeQuote img
	{
		max-height: 150px;
	}
	
	.bbCodeQuote iframe, .bbCodeQuote [data-s9e-mediaembed],
	.bbCodeQuote .fb_iframe_widget,
	.bbCodeQuote object,
	.bbCodeQuote embed
	{
		max-width: 200px;
		max-height: 150px;
	}
	
	.bbCodeQuote iframe:-webkit-full-screen
	{
		max-width: none;
		max-height: none;
	}
	
	.bbCodeQuote iframe:-moz-full-screen
	{
		max-width: none;
		max-height: none;
	}
	
	.bbCodeQuote iframe:-ms-fullscreen
	{
		max-width: none;
		max-height: none;
	}
	
	.bbCodeQuote iframe:fullscreen
	{
		max-width: none;
		max-height: none;
	}
	
.bbCodeSpoilerButton
{
	margin: 5px 0;
	max-width: 99%;
}

	.bbCodeSpoilerButton > span
	{
		display: inline-block;
		max-width: 100%;
		white-space: nowrap;
		text-overflow: ellipsis;
		overflow: hidden;
	}
	
.hasJs .bbCodeSpoilerText
{
	display: none;
	background-color: #F0F7FC;
padding: 5px;
margin-top: 5px;
margin-bottom: 5px;
border: 1px solid #D7EDFC;
border-radius: 5px;
overflow: auto;
/* margin-right: 200px; */

}

	.hasJs .bbCodeSpoilerText .bbCodeSpoilerText,
	.hasJs .bbCodeSpoilerText .bbCodeBlock,
	.hasJs .messageList.withSidebar .bbCodeSpoilerText
	{
		margin-right: 0;
	}
	
.NoJs .bbCodeSpoilerContainer
{
	background-color: #141414; /* fallback for browsers without currentColor */
	background-color: currentColor;
}

	.NoJs .bbCodeSpoilerContainer > .bbCodeSpoilerText
	{
		visibility: hidden;
	}

	.NoJs .bbCodeSpoilerContainer:hover
	{
		background-color: transparent;
	}
	
		.NoJs .bbCodeSpoilerContainer:hover > .bbCodeSpoilerText
		{
			visibility: visible;
		}


@media (max-width:800px)
{
	.Responsive .bbCodeBlock,
	.Responsive.hasJs .bbCodeSpoilerText
	{
		margin-right: 0;
	}
}


/* --- bbm_buttons.css --- */

span.mce_bbm_hl {background-position:-760px 0 !important}
span.mce_bbm_raw {background-position:-260px 0 !important}
span.mce_bbm_spoiler {
	background:url(styles/sedo/editor/adv_sprites.png) no-repeat 0 0 !important;
}

/* --- header_megamenu.css --- */

.megamenu_container {position:relative; float:right; margin:0 auto;}

#main-navigation {display:flex; flex-direction:row; flex-wrap:nowrap; justify-content:flex-end; font-size:0;}
#main-navigation > li {display:inline-block; padding:0; border-bottom:2px solid #414545; transition:border ease-out 0.2s; font-size:16px; line-height:19px;}
#main-navigation > li > a {display:block; padding:10px 14px; color:#FFF; transition:color ease-out 0.2s; font-family:Oswald,sans-serif; text-transform:uppercase;}
#main-navigation > li > a:hover,
#main-navigation > li > a:visited {text-decoration:none;}
#main-navigation > li:hover {border-bottom:2px solid #FC0;}
#main-navigation > li:hover > a {color:#FC0;}

.megamenu {list-style:none; z-index:9999;}
.megamenu li {border:none;}
.megamenu li.noactive {background:none;}

.megamenu > li:hover > a {color:#0B9EE3;}
.megamenu > li:hover > a span.nav-subtitle {color:#CCC;}

.megamenu li a span.nav-subtitle {color:#025485; font-size:11px; font-weight:normal;}

.megamenu li:hover .dropcontent {left:auto;}

.megamenu .col-first,
.megamenu .col_4,
.megamenu .col_8 {display:inline; position:relative; float:left; padding:0 1%;}
.megamenu .col-first,
.megamenu .col_4 {width:30%;}
.megamenu .col_8 {width:60%;}
.megamenu .col_4:first-child {padding-left:4%;}

.megamenu li .fullwidth {display:block; position:absolute; z-index:9998; left:1px; top:41px; width:100%; /*max-width:480px;*/ padding:24px 0; border-top:none; overflow:hidden; opacity:0; transition:opacity ease-out 0.25s; pointer-events:none;
	background-image:linear-gradient(rgba(0,0,0,0.8),rgba(0,0,0,0.6));
	background-image:url('data:image/png;base64,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');}
.megamenu li:hover .fullwidth {opacity:1; pointer-events:inherit;}

.megamenu li .fullwidth h4 {font-size:30px; color:#707070; margin:0; padding:0; line-height:30px;}
.megamenu li .fullwidth a:hover {color:#0CF;}
.megamenu li .fullwidth ul {list-style:none; margin:0; padding:0;}
.megamenu li .fullwidth ul ul {}
.megamenu li .fullwidth ul li {display:block; float:none;}
.megamenu li .fullwidth ul li a {display:block; float:none; height:auto; margin-bottom:5px; color:#FC0; font-family:Oswald,sans-serif; font-size:16px; font-weight:normal; line-height:20px; text-decoration:none; text-transform:uppercase;}
.megamenu li .fullwidth ul li li a {background:url('data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAAoAAAAKCAYAAACNMs+9AAAADUlEQVR4AWMYpGAUAAABmgABAec9CgAAAABJRU5ErkJggg==') left center no-repeat; color:#FFF;	font-size:14px; line-height:14px; height:auto; text-transform:none; margin-top:5px; padding-left:15px; text-transform:uppercase;}
.megamenu li .fullwidth ul li li a:hover {background:url('data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAAoAAAAKAQAAAAClSfIQAAAADUlEQVR4AWP8fxAPAgAIiBGLEePG8AAAAABJRU5ErkJggg==') left center no-repeat;}
.megamenu li .fullwidth ul li li ul li a {color:#FFF; font-size:11px; line-height:12px; height:auto; text-transform:none; margin-left:10px;}

.megamenu li .fullwidth li div {font-size:20px;}

.menu-content {position:relative; z-index:2;}

/* .megamenu li .dropcontent {position:absolute; left:-9999em; top:63px; margin:0 auto; padding:24px 0 10px; border:1px solid #1b1b1b; border-top:none; border-radius:0 0 4px 4px; background:#222; text-align:left; z-index:9998;}
.megamenu li .dropfirst {margin:0 auto 0 -1px;} */  /* Fixes a 1px issue for the 1st drop down */
/* Showing Drop Down on Mouse Hover - Left aligned */
/* .megamenu li:hover .dropcontent {left:auto!important;}
.megamenu li:hover .dropcontent.rightanchor {right:0!important;} */

/* --- header_megamenu_forum_additions.css --- */

.megamenu #menu-forums {border-bottom:2px solid #CA0; /*margin-bottom:-2px;*/}
.megamenu #menu-forums a {color:#CA0;}

/* --- likes_summary.css --- */

.likesSummary
{
	overflow: hidden; zoom: 1;
	font-size: 11px;
}

	.LikeText
	{
		float: left;
	}
	
	.likeInfo
	{
		float: right;
	}

/* --- login_bar.css --- */

/** Login bar basics **/

#loginBar
{
	color: #CFE3F1;
background-color: #2B485C;
border-bottom: 0 solid #032A46;
border-bottom-right-radius: 0;
position: relative;
z-index: 1;

}

	#loginBar .ctrlWrapper
	{
		margin: 0 10px;
	}

	#loginBar .pageContent
	{
		padding-top: 5px;
		position: relative;
		_height: 0px;
	}

	#loginBar a
	{
		color: #6CB2E4;

	}

	#loginBar form
	{
		padding: 5px 0;
margin: 0 auto;
display: none;
line-height: 20px;
position: relative;

	}
	
		#loginBar .xenForm .ctrlUnit,		
		#loginBar .xenForm .ctrlUnit > dt label
		{
			margin: 0;
			border: none;
		}
	
		#loginBar .xenForm .ctrlUnit > dd
		{
			position: relative;
		}
	
	#loginBar .lostPassword,
	#loginBar .lostPasswordLogin
	{
		font-size: 11px;
	}
	
	#loginBar .rememberPassword
	{
		font-size: 11px;
	}

	#loginBar .textCtrl
	{
		color: #000000;
background-color: #D7EDFC;
border-color: #65A5D1;

	}
	
	#loginBar .textCtrl[type=text]
	{
		font-weight: bold;
font-size: 18px;

	/*color: #FFCC00;*/
	}

	#loginBar .textCtrl:-webkit-autofill /* http://code.google.com/p/chromium/issues/detail?id=1334#c35 */
	{
		background: #D7EDFC !important;
		color: #000000;
	}

	#loginBar .textCtrl:focus
	{
		background-color: #000000;

	}
	
	#loginBar input.textCtrl.disabled
	{
		color: #CFE3F1;
background-color: #032A46;
border-style: dashed;

	}
	
	#loginBar .button
	{
		min-width: 85px;
		*width: 85px;
	}
	
		#loginBar .button.primary
		{
			font-weight: bold;
		}
		
/** changes when eAuth is present **/

#loginBar form.eAuth
{
	-x-max-width: 700px; /* normal width + 170px */
}

	#loginBar form.eAuth .ctrlWrapper
	{
		border-right: 1px dotted #176093;
		margin-right: 200px;
		box-sizing: border-box;
	}

	#loginBar form.eAuth #eAuthUnit
	{
		position: absolute;
		top: 0px;
		right: 10px;
	}

		#eAuthUnit li
		{
			margin-top: 10px;
			line-height: 0;
		}
	
/** handle **/

#loginBar #loginBarHandle
{
	font-size: 13px;
color: #F0F7FC;
background-color: #2B485C;
padding: 0 10px;
margin-right: 20px;
border-bottom-right-radius: 10px;
border-bottom-left-radius: 10px;
position: absolute;
right: 0px;
bottom: -25px;
text-align: center;
z-index: 1;
line-height: 2;
box-shadow: 0px 2px 5px #032A46;

}


@media (max-width:800px)
{
	.Responsive #loginBar form.eAuth .ctrlWrapper
	{
		border-right: none;
		margin-right: 10px;
	}

	.Responsive #loginBar form.eAuth #eAuthUnit
	{
		position: static;
		width: 180px;
		margin: 0 auto 10px;
	}
}


/* --- logo_block.css --- */

.container-fluid::after{clear:both}
.container-fluid::before,.container-fluid::after{display:table;line-height:0;content:""}
.container-fluid{padding-right:20px;padding-left:20px;*zoom:1}

.row-fluid {width:100%;*zoom:1;}
.row-fluid::after{clear:both}
.row-fluid::before,.row-fluid::after{display:table;line-height:0;content:""}
.row-fluid [class*="span"]{display:block;float:left;width:100%;min-height:30px;margin-left:2.1276595744681%;*margin-left:2.0744680851064%;-webkit-box-sizing:border-box;-moz-box-sizing:border-box;box-sizing:border-box}
.row-fluid [class*="span"]:first-child{margin-left:0}
[class*="span"]{float:left;min-height:1px;margin-left:20px}
.row-fluid .span6{width:48.936170212766%;*width:48.882978723404%}
.span6{width:460px}
@media screen only and (min-width:1200px) {
.row-fluid [class*="span"]{display:block;float:left;width:100%;min-height:30px;margin-left:2.5641025641026%;*margin-left:2.5109110747409%;-webkit-box-sizing:border-box;-moz-box-sizing:border-box;box-sizing:border-box}
[class*="span"]{float:left;min-height:1px;margin-left:30px}
.row-fluid .span6{width:48.717948717949%;*width:48.664757228587%}
.span6{width:570px}
}

.wrap {width:100%; max-width:1024px; margin:0 auto; position:relative;}

.header-container {display:flex; flex-direction:row; flex-wrap:nowrap; justify-content:space-between;}

#logoBlock .full-logo {display:none;}
#logoBlock .half-logo,
#logoBlock .half-menu {display:block; flex:1 1 auto;}
/*#logoBlock .half-logo {}*/
#logoBlock .half-menu {padding-top:36px;}
@media screen and (max-width:719px) {
  #logoBlock .half-logo,
  #logoBlock .half-menu {display:none;}
  #logoBlock .full-logo {display:block;}
}
/*#site-header {padding:40px 0 0}*/
#header-controls {position:absolute;top:-25px;right:20px;color:#FFF;}

.simple-menu {width:100%!important;margin-left:0!important;padding-left:0!important;margin-top:20px;text-align:center}
#sidebar-fixed-menu {position:fixed;top:200px;right:0;min-width:200px;z-index:100}
#sidebar-fixed-menu .well {padding:0;border-radius:0}

/* --- message.css --- */



.messageList
{
	background-color: #D6E0EA;
padding: 10px;

}

.messageList .message
{
	background-color: #FCFCFF;
padding: 10px 10px 30px;
border-top: 1px solid #FFFFFF;
border-bottom:  1px solid rgb(127,127,127); border-bottom:  1px solid rgba(127,127,127, 0.3); _border-bottom:  1px solid rgb(127,127,127);

}

/* clearfix */ .messageList .message { zoom: 1; } .messageList .message:after { content: '.'; display: block; height: 0; clear: both; visibility: hidden; }

/*** Message block ***/

.message .messageInfo
{
	background-color: #FCFCFF;
padding: 0;
margin-left: 200px;
border-bottom: 1px none black;

	zoom: 1;
}

	.message .newIndicator
	{
		font-size: 11px;
color: #176093;
background-color: #D7EDFC;
padding: 1px 5px;
margin: -5px -5px 5px 5px;
border: 1px solid #6CB2E4;
border-radius: 3px;
border-top-right-radius: 0px;
display: block;
float: right;
position: relative;
background-image: linear-gradient(#F0F7FC,#D7EDFC);
box-shadow: 1px 1px 3px rgba(0,0,0, 0.25);

		
		margin-right: -25px;
	}
	
		.message .newIndicator span
		{
			background-color: #6CB2E4;
border-top-right-radius: 3px;
position: absolute;
top: -4px;
right: -1px;
width: 5px;
height: 4px;

		}

	.message .messageContent
	{
		background-color: #FCFCFF;
padding-bottom: 2px;
min-height: 100px;
overflow: hidden;
*zoom: 1;
/*padding: 12px 18px;
		box-shadow: 0px 9px 3px -7px #999;*/

	}
	
	.message .messageTextEndMarker
	{
		height: 0;
		font-size: 0;
		overflow: hidden;
	}
	
	.message .editDate
	{
		text-align: right;
		margin-top: 5px;
		font-size: 11px;
		color: #969696;
	}

	.message .signature
	{
		font-size: 12px;
color: #969696;
padding: 12px 0 0;
margin-top: 15px;
border-top: 1px dotted #E5EFF9;

	}

	.message .messageMeta
	{
		font-size: 11px;
padding: 15px 5px 5px;
margin: -5px;
overflow: hidden;
zoom: 1;

	}

		.message .privateControls
		{
			float: left;

		}

		.message .publicControls
		{
			float: right;

		}
		
			.message .privateControls .item
			{
				margin-right: 10px;
				float: left;
			}

				.message .privateControls .item:last-child
				{
					margin-right: 0;
				}

			.message .publicControls .item
			{
				margin-left: 10px;
				float: left;
			}
	
				.message .messageMeta .control
				{
					
				}
				
					.message .messageMeta .control:focus
					{
						
					}
				
					.message .messageMeta .control:hover
					{
						
					}
				
					.message .messageMeta .control:active
					{
						
					}
	/*** multiquote +/- ***/
			
	.message .publicControls .MultiQuoteControl
	{
		padding-left: 4px;
		padding-right: 4px;
		border-radius: 2px;
		margin-left: 6px;
		margin-right: -4px;
	}
	
	
	.message .publicControls .MultiQuoteControl.active
	{
		background-color: #D7EDFC;
	}
	
		.messageNotices li
	{
		font-size: 11px;
background: #E5EFF9 url('styles/default/xenforo/gradients/form-button-white-25px.png') repeat-x top;
padding: 5px;
margin: 10px 0;
border: 1px solid #E5EFF9;
border-radius: 5px;
line-height: 16px;

	}
	
		.messageNotices .icon
		{
			float: right;
			width: 16px;
			height: 16px;
			background: url('styles/default/xenforo/xenforo-ui-sprite.png') no-repeat 1000px 1000px;
		}
	
			.messageNotices .warningNotice .icon { background-position: -48px -32px; }		
			.messageNotices .deletedNotice .icon { background-position: -64px -32px; }		
			.messageNotices .moderatedNotice .icon {background-position: -32px -16px; }
	
	.message .likesSummary
	{
		padding: 5px;
margin-top: 10px;
border: 1px solid #D7EDFC;
border-radius: 5px;

	}
	
	.message .messageText > *:first-child
	{
		margin-top: 0;
	}

/* inline moderation changes */

.InlineModChecked .messageUserBlock,
.InlineModChecked .messageInfo,
.InlineModChecked .messageContent,
.InlineModChecked .messageNotices,
.InlineModChecked .bbCodeBlock .type,
.InlineModChecked .bbCodeBlock blockquote,
.InlineModChecked .attachedFiles .attachedFilesHeader,
.InlineModChecked .attachedFiles .attachmentList {background:transparent;}
.InlineModChecked.message/*, .InlineModChecked .userText*/ {background-color:#CFE3F1;/*background-image:linear-gradient(#CFE3F1,#F0F7FC);*/border-color:#E5EFF9;}

{
	background-color: #F0F7FC;
background-image: linear-gradient(#D7EDFC,#F0F7FC);

}

.InlineModChecked .messageUserBlock div.avatarHolder/*,
.InlineModChecked .messageUserBlock .extraUserInfo*/
{
	background: transparent;
}

.InlineModChecked .messageUserBlock .arrow span
{
	border-left-color: #FFFFCC;
}

/* message list */

.messageList .newMessagesNotice
{
	margin: 10px auto;
	padding: 5px 10px;
	border-radius: 5px;
	border: 1px solid #CFE3F1;
	background-color:#D7EDFC;
	background-image:linear-gradient(#D7EDFC,#F0F7FC);
	font-size: 11px;
}

/* deleted / ignored message placeholder */

.messageList .message.placeholder
{
}

.messageList .placeholder .placeholderContent
{	
	overflow: hidden; zoom: 1;
	color: #65A5D1;
	font-size: 11px;
}

	.messageList .placeholder a.avatar
	{
		float: left;
		display: block;
	}
	
		.messageList .placeholder a.avatar img
		{
			display: block;
			width: 32px;
			height: 32px;
		}
		
	.messageList .placeholder .privateControls
	{
		margin-top: -5px;
	}
	

/* messages remaining link */

.postsRemaining a,
a.postsRemaining
{
	font-size: 11px;
	color: #969696;
}


@media (max-width:800px)
{
	.Responsive .message .newIndicator
	{
		margin-right: 0;
		border-top-right-radius: 3px;
	}
	
		.Responsive .message .newIndicator span
		{
			display: none;
		}
}

@media (max-width:480px)
{
	.Responsive .message .messageInfo
	{
		margin-left: 0;
		padding: 0 10px;
	}

	.Responsive .message .messageContent
	{
		min-height: 0;
	}	

	.Responsive .message .newIndicator
	{
		margin-right: -5px;
		margin-top: -16px;
	}

	.Responsive .message .postNumber,
	.Responsive .message .authorEnd
	{
		display: none;
	}
	
	.Responsive .message .signature
	{
		display: none;
	}
	
	.Responsive .messageList .placeholder a.avatar
	{
		margin-right: 10px;
	}
}


/* --- message_user_info.css --- */

.messageUserInfo
{
	float: left;
width: 184px;

}

	.messageUserBlock
	{
		
		
		position: relative;
	}
		
		.messageUserBlock div.avatarHolder
		{
			padding: 10px;
margin: 0 auto;
max-width: 100px;

			
			position: relative;	
		}
		
			.messageUserBlock div.avatarHolder .avatar
			{
				display: block;
				font-size: 0;
			}
			
			.messageUserBlock div.avatarHolder .onlineMarker
			{
			}
			
		.messageUserBlock h3.userText
		{
			padding: 6px;

		}
		
		.messageUserBlock .userBanner
		{
			display: block;
			margin-bottom: 5px;
			margin-left: -12px;
			margin-right: -12px;
		}
		
		.messageUserBlock .userBanner:last-child
		{
			margin-bottom: 0;
		}
	
		.messageUserBlock a.username
		{
			font-weight: bold;
display: block;
overflow: hidden;
line-height: 16px;

			
		}
		
		.messageUserBlock .userTitle
		{
			font-size: 11px;
display: block;
/*margin-bottom: 5px;*/

		}
		
		.messageUserBlock .extraUserInfo
		{
			font-size: 10px;
padding: 5px 0;

		}
		
			.messageUserBlock .extraUserInfo dl
			{
				margin: 2px 0 0;
				padding:0 6px;
			}
							
			.messageUserBlock .extraUserInfo img
			{
				max-width: 100%;
			}
		
		.messageUserBlock .arrow
		{
			position: absolute;
			top: 10px;
			right: -10px;
			
			display: block;
			width: 0px;
			height: 0px;
			line-height: 0px;
			
			border: 10px solid transparent;
			border-left-color: ;
			-moz-border-left-colors: ;
			border-right: none;
			
			/* Hide from IE6 */
			_display: none;
		}
		
			.messageUserBlock .arrow span
			{
				position: absolute;
				top: -10px;
				left: -11px;
				
				display: block;
				width: 0px;
				height: 0px;
				line-height: 0px;
				
				border: 10px solid transparent;
				border-left-color: ;
				-moz-border-left-colors: ;
				border-right: none;
			}


@media (max-width:480px)
{
	.Responsive .messageUserInfo
	{
		float: none;
		width: auto; 
	}

	.Responsive .messageUserBlock
	{
		overflow: hidden;
		margin-bottom: 5px;
		position: relative;
	}

	.Responsive .messageUserBlock div.avatarHolder
	{
		float: left;
		padding: 5px;
	}

		.Responsive .messageUserBlock div.avatarHolder .avatar img
		{
			width: 48px;
			height: 48px;
		}
		
		.Responsive .messageUserBlock div.avatarHolder .onlineMarker
		{
			top: 4px;
			left: 4px;
			border-width: 6px;
		}

	.Responsive .messageUserBlock h3.userText
	{
		margin-left: 64px;
	}
	
	.Responsive .messageUserBlock .userBanner
	{
		max-width: 150px;
		margin-left: 0;
		margin-right: 0;
		border-top-left-radius: 3px;
		border-top-right-radius: 3px;
		position: static;
		display: inline-block;
	}
	
		.Responsive .messageUserBlock .userBanner span
		{
			display: none;
		}

	.Responsive .messageUserBlock .extraUserInfo
	{
		display: none;
	}

	.Responsive .messageUserBlock .arrow
	{
		display: none;
	}
}


/* --- nat_public_css.css --- */

.natMenuLevel0
{
	padding-left: 0px;
}

.natMenuLevel1
{
	padding-left: 10px;
}

.natMenuLevel2
{
	padding-left: 20px;
}

.natMenuLevel3
{
	padding-left: 30px;
}

.natMenuLevel4
{
	padding-left: 40px;
}

.natMenuLevel5
{
	padding-left: 50px;
}

.natMenuLevel6
{
	padding-left: 60px;
}

.natMenuLevel7
{
	padding-left: 70px;
}

.natMenuLevel8
{
	padding-left: 80px;
}

.natMenuLevel9
{
	padding-left: 90px;
}

.natMenuLevel10
{
	padding-left: 100px;
}



/* STYLING TO MAKE COLUMN MENUS WORK */
div.natJSMenuColumns
{
	background-color: #F0F7FC;
	background-color: rgba(240, 247, 252, 0.96);
}

/* STYLING TO MAKE COLUMN MENUS WORK */
div.natJSMenuColumns ul
{
	float: left;
	border-bottom: 0px;
	background-color: transparent !important;
	max-height: none !important;
}







/* --- online_marker.css --- */

.messageUserBlock div.avatarHolder .onlineMarker
{
	position: absolute;
	top:11px;
	left:11px;
	border: 11px solid transparent;
border-top-color: #7D0;
border-left-color: #7D0;
border-radius: 3px;
/*	border:5px solid #7D0;
	border-radius:50%;
	box-shadow:0 0 2px #000,0 0 10px #7D0,0 0 15px #7D0,0 0 20px #7D0;*/

}


/* --- share_page.css --- */

.sharePage
{
}

/* clearfix */ .sharePage { zoom: 1; } .sharePage:after { content: '.'; display: block; height: 0; clear: both; visibility: hidden; }

	.sharePage .shareControl
	{
		float: left;
	}
	
	.sharePage .tweet
	{
		margin-right: 30px;
	}

	.sharePage .facebookLike .label
	{
		font-size: 11px;
		line-height: 24px;
		float: left;
		margin-right: 7px;
		display: none;
	}
	
	.sharePage iframe
	{
		height: 20px;
	}
	
	.sharePage .facebookLike iframe
	{
		z-index: 52;
	}
	



@media (max-width:480px)
{
	.Responsive .sharePage
	{
		display: none;
	}
}


/* --- thread_view.css --- */

.thread_view .threadAlerts
{
	margin: 1px 0;
	border: 1px solid #176093;
	border-radius: 5px;
	padding: 5px;
	background-color:#D7EDFC;
	background-image:linear-gradient(#D7EDFC,#6CB2E4);
	font-size: 11px;
	line-height: 16px;
}
	
	.thread_view .threadAlerts dt
	{
		color: #032A46;
		display: inline;
	}
	
	.thread_view .threadAlerts dd
	{
		color: #2B485C;
		font-weight: bold;
		display: inline;
	}
	
		.thread_view .threadAlerts .icon
		{
			float: right;
			width: 16px;
			height: 16px;
			margin-left: 5px;
			background: url('styles/default/xenforo/xenforo-ui-sprite.png') no-repeat -1000px -1000px;
		}
		
			.thread_view .threadAlerts .deletedAlert .icon { background-position: -64px -32px; }
			.thread_view .threadAlerts .moderatedAlert .icon { background-position: -32px -16px; }
			.thread_view .threadAlerts .lockedAlert .icon { background-position: -16px -16px; }
	
.thread_view .threadAlerts + * > .messageList
{
	border-top: none;
}

.thread_view .threadNotices
{
	background-color: #F0F7FC;
	border: 1px solid #CFE3F1;
	border-radius: 5px;
	padding: 10px;
	margin: 10px auto;
}

.thread_view .InlineMod
{
	overflow: hidden; zoom: 1;
}
