/* $XdotOrg: xc/programs/Xserver/hw/xfree86/loader/dixsym.c,v 1.19 2005/10/01 17:30:58 herrb Exp $ */
/* $XFree86: xc/programs/Xserver/hw/xfree86/loader/dixsym.c,v 1.63 2003/12/03
 * 17:11:29 tsi Exp $ */

/*
 * Copyright 1995-1998 by Metro Link, Inc.
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation, and that the name of Metro Link, Inc. not be used in
 * advertising or publicity pertaining to distribution of the software without
 * specific, written prior permission.  Metro Link, Inc. makes no
 * representations about the suitability of this software for any purpose.
 *  It is provided "as is" without express or implied warranty.
 *
 * METRO LINK, INC. DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL METRO LINK, INC. BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */
/*
 * Copyright (c) 1997-2003 by The XFree86 Project, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name of the copyright holder(s)
 * and author(s) shall not be used in advertising or otherwise to promote
 * the sale, use or other dealings in this Software without prior written
 * authorization from the copyright holder(s) and author(s).
 */

#undef DBMALLOC
#ifdef HAVE_XORG_CONFIG_H
#include <xorg-config.h>
#endif

#include "sym.h"
#include "colormap.h"
#include "cursor.h"
#include "cursorstr.h"
#include "dix.h"
#include "dixevents.h"
#include "dixfont.h"
#include "dixstruct.h"
#include "misc.h"
#include "globals.h"
#include "os.h"
#include "osdep.h"
#include "resource.h"
#include "servermd.h"
#include "scrnintstr.h"
#include "windowstr.h"
#include "extension.h"
#define EXTENSION_PROC_ARGS void *
#include "extnsionst.h"
#include "swaprep.h"
#include "swapreq.h"
#include "inputstr.h"
#include <X11/extensions/XIproto.h>
#include "exevents.h"
#include "extinit.h"
#ifdef XV
#include "xvmodproc.h"
#endif
#include "dgaproc.h"
#ifdef RENDER
#include "mipict.h"
#include "renderedge.h"
#endif
#include "selection.h"
#ifdef XKB
#include <X11/extensions/XKBsrv.h>
extern int XkbDfltRepeatDelay, XkbDfltRepeatInterval;
#endif

extern Selection *CurrentSelections;
extern int NumCurrentSelections;

/* DIX things */

LOOKUP dixLookupTab[] = {

    /* dix */
    /* atom.c */
    SYMFUNC(MakeAtom)
    SYMFUNC(ValidAtom)
    /* colormap.c */
    SYMFUNC(AllocColor)
    SYMFUNC(CreateColormap)
    SYMFUNC(FakeAllocColor)
    SYMFUNC(FakeFreeColor)
    SYMFUNC(FreeColors)
    SYMFUNC(StoreColors)
    SYMFUNC(TellLostMap)
    SYMFUNC(TellGainedMap)
    SYMFUNC(QueryColors)
    /* cursor.c */
    SYMFUNC(FreeCursor)
    /* devices.c */
    SYMFUNC(Ones)
    SYMFUNC(InitButtonClassDeviceStruct)
    SYMFUNC(InitFocusClassDeviceStruct)
    SYMFUNC(InitLedFeedbackClassDeviceStruct)
    SYMFUNC(InitPtrFeedbackClassDeviceStruct)
    SYMFUNC(InitKbdFeedbackClassDeviceStruct)
    SYMFUNC(InitIntegerFeedbackClassDeviceStruct)
    SYMFUNC(InitStringFeedbackClassDeviceStruct)
    SYMFUNC(InitBellFeedbackClassDeviceStruct)
    SYMFUNC(InitValuatorClassDeviceStruct)
    SYMFUNC(InitKeyClassDeviceStruct)
    SYMFUNC(InitKeyboardDeviceStruct)
    SYMFUNC(SendMappingNotify)
    SYMFUNC(InitPointerDeviceStruct)
    SYMFUNC(LookupKeyboardDevice)
    SYMFUNC(LookupPointerDevice)
    /* dispatch.c */
    SYMFUNC(SetInputCheck)
    SYMFUNC(SendErrorToClient)
    SYMFUNC(UpdateCurrentTime)
    SYMFUNC(UpdateCurrentTimeIf)
    SYMFUNC(ProcBadRequest)
    SYMVAR(dispatchException)
    SYMVAR(isItTimeToYield)
    SYMVAR(ClientStateCallback)
    SYMVAR(ServerGrabCallback)
    SYMVAR(CurrentSelections)
    SYMVAR(NumCurrentSelections)
    /* dixfonts.c */
    SYMFUNC(CloseFont)
    SYMFUNC(FontToXError)
    SYMFUNC(LoadGlyphs)
    SYMVAR(fpe_functions)
    /* dixutils.c */
    SYMFUNC(AddCallback)
    SYMFUNC(ClientSleep)
    SYMFUNC(ClientTimeToServerTime)
    SYMFUNC(ClientWakeup)
    SYMFUNC(CompareTimeStamps)
    SYMFUNC(CopyISOLatin1Lowered)
    SYMFUNC(DeleteCallback)
    SYMFUNC(LookupClient)
    SYMFUNC(LookupDrawable)
    SYMFUNC(LookupWindow)
    SYMFUNC(NoopDDA)
    SYMFUNC(QueueWorkProc)
    SYMFUNC(RegisterBlockAndWakeupHandlers)
    SYMFUNC(RemoveBlockAndWakeupHandlers)
#ifdef XCSECURITY
    SYMFUNC(SecurityLookupDrawable)
    SYMFUNC(SecurityLookupWindow)
#endif
    /* events.c */
    SYMFUNC(CheckCursorConfinement)
    SYMFUNC(DeliverEvents)
    SYMFUNC(NewCurrentScreen)
    SYMFUNC(PointerConfinedToScreen)
    SYMFUNC(TryClientEvents)
    SYMFUNC(WriteEventsToClient)
    SYMFUNC(GetCurrentRootWindow)
    SYMFUNC(GetSpritePosition)
    SYMFUNC(GetSpriteWindow)
    SYMFUNC(GetSpriteCursor)
    SYMFUNC(WindowsRestructured)
    SYMVAR(DeviceEventCallback)
    SYMVAR(EventCallback)
    SYMVAR(inputInfo)
    SYMFUNC(SetCriticalEvent)
#ifdef PANORAMIX
    SYMFUNC(XineramaGetCursorScreen)
#endif
    /* property.c */
    SYMFUNC(ChangeWindowProperty)
    /* extension.c */
    SYMFUNC(AddExtension)
    SYMFUNC(AddExtensionAlias)
    SYMFUNC(CheckExtension)
    SYMFUNC(DeclareExtensionSecurity)
    SYMFUNC(MinorOpcodeOfRequest)
    SYMFUNC(StandardMinorOpcode)
#ifdef XEVIE
    SYMVAR(xeviehot)
    SYMVAR(xeviewin)
#endif
    /* gc.c */
    SYMFUNC(CopyGC)
    SYMFUNC(CreateGC)
    SYMFUNC(CreateScratchGC)
    SYMFUNC(ChangeGC)
    SYMFUNC(dixChangeGC)
    SYMFUNC(DoChangeGC)
    SYMFUNC(FreeGC)
    SYMFUNC(FreeScratchGC)
    SYMFUNC(GetScratchGC)
    SYMFUNC(SetClipRects)
    SYMFUNC(ValidateGC)
    SYMFUNC(VerifyRectOrder)
    SYMFUNC(SetDashes)
    /* globals.c */
    SYMVAR(ScreenSaverTime)
#ifdef DPMSExtension
    SYMVAR(DPMSEnabled)
    SYMVAR(DPMSCapableFlag)
    SYMVAR(DPMSOffTime)
    SYMVAR(DPMSPowerLevel)
    SYMVAR(DPMSStandbyTime)
    SYMVAR(DPMSSuspendTime)
    SYMVAR(DPMSEnabledSwitch)
    SYMVAR(DPMSDisabledSwitch)
    SYMVAR(defaultDPMSEnabled)
#endif
    /* bigreq */
    SYMVAR(maxBigRequestSize)
#ifdef XV
    /* XXX These are exported from the DDX, not DIX. */
    SYMVAR(XvScreenInitProc)
    SYMVAR(XvGetScreenIndexProc)
    SYMVAR(XvGetRTPortProc)
    SYMVAR(XvMCScreenInitProc)
#endif
    SYMVAR(ScreenSaverBlanking)
    SYMVAR(WindowTable)
    SYMVAR(clients)
    SYMVAR(currentMaxClients)
    SYMVAR(currentTime)
    SYMVAR(defaultColorVisualClass)
    SYMVAR(display)
    SYMVAR(globalSerialNumber)
    SYMVAR(lastDeviceEventTime)
    SYMVAR(monitorResolution)
    SYMVAR(permitOldBugs)
    SYMVAR(screenInfo)
    SYMVAR(serverClient)
    SYMVAR(serverGeneration)
    /* main.c */
    SYMFUNC(NotImplemented)
    SYMVAR(PixmapWidthPaddingInfo)
    /* pixmap.c */
    SYMFUNC(AllocatePixmap)
    SYMFUNC(GetScratchPixmapHeader)
    SYMFUNC(FreeScratchPixmapHeader)
    /* privates.c */
    SYMFUNC(AllocateClientPrivate)
    SYMFUNC(AllocateClientPrivateIndex)
    SYMFUNC(AllocateGCPrivate)
    SYMFUNC(AllocateGCPrivateIndex)
    SYMFUNC(AllocateWindowPrivate)
    SYMFUNC(AllocateWindowPrivateIndex)
    SYMFUNC(AllocateScreenPrivateIndex)
    SYMFUNC(AllocateColormapPrivateIndex)
    SYMFUNC(AllocateDevicePrivateIndex)
    SYMFUNC(AllocateDevicePrivate)
#ifdef PIXPRIV
    SYMFUNC(AllocatePixmapPrivateIndex)
    SYMFUNC(AllocatePixmapPrivate)
#endif
    /* resource.c */
    SYMFUNC(AddResource)
    SYMFUNC(ChangeResourceValue)
    SYMFUNC(CreateNewResourceClass)
    SYMFUNC(CreateNewResourceType)
    SYMFUNC(FakeClientID)
    SYMFUNC(FreeResource)
    SYMFUNC(FreeResourceByType)
    SYMFUNC(GetXIDList)
    SYMFUNC(GetXIDRange)
    SYMFUNC(LookupIDByType)
    SYMFUNC(LookupIDByClass)
    SYMFUNC(LegalNewID)
#ifdef XCSECURITY
    SYMFUNC(SecurityLookupIDByClass)
    SYMFUNC(SecurityLookupIDByType)
#endif
    SYMFUNC(FindClientResourcesByType)
    SYMFUNC(FindAllClientResources)
    SYMVAR(lastResourceType)
    SYMVAR(TypeMask)
#ifdef RES
    SYMFUNC(RegisterResourceName)
    SYMVAR(ResourceNames)
#endif
    /* swaprep.c */
    SYMFUNC(CopySwap32Write)
    SYMFUNC(Swap32Write)
    SYMFUNC(SwapConnSetupInfo)
    SYMFUNC(SwapConnSetupPrefix)
    /* swapreq.c */
    SYMFUNC(SwapShorts)
    SYMFUNC(SwapLongs)
    SYMFUNC(SwapColorItem)
    /* tables.c */
    SYMVAR(EventSwapVector)
    SYMVAR(ReplySwapVector)
    SYMVAR(ProcVector)
    /* window.c */
    SYMFUNC(ChangeWindowAttributes)
    SYMFUNC(CheckWindowOptionalNeed)
    SYMFUNC(CreateUnclippedWinSize)
    SYMFUNC(CreateWindow)
    SYMFUNC(FindWindowWithOptional)
    SYMFUNC(GravityTranslate)
    SYMFUNC(MakeWindowOptional)
    SYMFUNC(MapWindow)
    SYMFUNC(MoveWindowInStack)
    SYMFUNC(NotClippedByChildren)
    SYMFUNC(ResizeChildrenWinSize)
    SYMFUNC(SaveScreens)
    SYMFUNC(SendVisibilityNotify)
    SYMFUNC(SetWinSize)
    SYMFUNC(SetBorderSize)
    SYMFUNC(TraverseTree)
    SYMFUNC(UnmapWindow)
    SYMFUNC(WalkTree)
    SYMVAR(deltaSaveUndersViewable)
    SYMVAR(numSaveUndersViewable)
    SYMVAR(savedScreenInfo)
    SYMVAR(screenIsSaved)

    /*os/ */
    /* access.c */
    SYMFUNC(LocalClient)
    /* utils.c */
    SYMFUNC(Xstrdup)
    SYMFUNC(XNFstrdup)
    SYMVAR(Must_have_memory)
    SYMFUNC(AdjustWaitForDelay)
    SYMVAR(noTestExtensions)
    SYMFUNC(GiveUp)

#ifdef BIGREQS
    SYMVAR(noBigReqExtension)
#endif
#ifdef COMPOSITE
    SYMVAR(noCompositeExtension)
#endif
#ifdef DAMAGE
    SYMVAR(noDamageExtension)
#endif
#ifdef DBE
    SYMVAR(noDbeExtension)
#endif
#ifdef DPSEXT
    SYMVAR(noDPSExtension)
#endif
#ifdef DPMSExtension
    SYMVAR(noDPMSExtension)
#endif
#ifdef EVI
    SYMVAR(noEVIExtension)
#endif
#ifdef FONTCACHE
    SYMVAR(noFontCacheExtension)
#endif
#ifdef GLXEXT
    SYMVAR(noGlxExtension)
#endif
#ifdef LBX
    SYMVAR(noLbxExtension)
#endif
#ifdef SCREENSAVER
    SYMVAR(noScreenSaverExtension)
#endif
#ifdef MITSHM
    SYMVAR(noMITShmExtension)
#endif
#ifdef MITMISC
    SYMVAR(noMITMiscExtension)
#endif
#ifdef MULTIBUFFER
    SYMVAR(noMultibufferExtension)
#endif
#ifdef RANDR
    SYMVAR(noRRExtension)
#endif
#ifdef RENDER
    SYMVAR(noRenderExtension)
#endif
#ifdef SHAPE
    SYMVAR(noShapeExtension)
#endif
#ifdef XCSECURITY
    SYMVAR(noSecurityExtension)
#endif
#ifdef XSYNC
    SYMVAR(noSyncExtension)
#endif
#ifdef TOGCUP
    SYMVAR(noXcupExtension)
#endif
#ifdef RES
    SYMVAR(noResExtension)
#endif
#ifdef XAPPGROUP
    SYMVAR(noXagExtension)
#endif
#ifdef XCMISC
    SYMVAR(noXCMiscExtension)
#endif
#ifdef XEVIE
    SYMVAR(noXevieExtension)
#endif
#ifdef XF86BIGFONT
    SYMVAR(noXFree86BigfontExtension)
#endif
#ifdef XFreeXDGA
    SYMVAR(noXFree86DGAExtension)
#endif
#ifdef XF86DRI
    SYMVAR(noXFree86DRIExtension)
#endif
#ifdef XF86MISC
    SYMVAR(noXFree86MiscExtension)
#endif
#ifdef XF86VIDMODE
    SYMVAR(noXFree86VidModeExtension)
#endif
#ifdef XFIXES
    SYMVAR(noXFixesExtension)
#endif
#ifdef XKB
/* |noXkbExtension| is defined in xc/programs/Xserver/xkb/xkbInit.c */
    SYMVAR(noXkbExtension)
#endif
#ifdef PANORAMIX
    SYMVAR(noPanoramiXExtension)
#endif
#ifdef XINPUT
    SYMVAR(noXInputExtension)
#endif
#ifdef XIDLE
    SYMVAR(noXIdleExtension)
#endif
#ifdef XV
    SYMVAR(noXvExtension)
#endif

    /* log.c */
    SYMFUNC(LogVWrite)
    SYMFUNC(LogWrite)
    SYMFUNC(LogVMessageVerb)
    SYMFUNC(LogMessageVerb)
    SYMFUNC(LogMessage)
    SYMFUNC(FatalError)
    SYMFUNC(VErrorF)
    SYMFUNC(ErrorF)
    SYMFUNC(Error)
    /* xalloc.c */
    SYMFUNC(XNFalloc)
    SYMFUNC(XNFcalloc)
    SYMFUNC(XNFrealloc)
    SYMFUNC(Xalloc)
    SYMFUNC(Xcalloc)
    SYMFUNC(Xfree)
    SYMFUNC(Xrealloc)
    /* WaitFor.c */
    SYMFUNC(TimerFree)
    SYMFUNC(TimerSet)
    SYMFUNC(TimerCancel)
#ifdef DPMSExtension
    SYMFUNC(SetDPMSTimers)
#endif
    /* io.c */
    SYMFUNC(WriteToClient)
    SYMFUNC(SetCriticalOutputPending)
    SYMVAR(FlushCallback)
    SYMVAR(ReplyCallback)
    SYMVAR(SkippedRequestsCallback)
    SYMFUNC(ResetCurrentRequest)
    /* connection.c */
    SYMFUNC(IgnoreClient)
    SYMFUNC(AttendClient)
    SYMFUNC(AddEnabledDevice)
    SYMFUNC(RemoveEnabledDevice)
    SYMFUNC(MakeClientGrabPervious)
    SYMFUNC(MakeClientGrabImpervious)
    SYMVAR(GrabInProgress)

#ifdef XKB
    /* xkb/xkbInit.c */
    SYMFUNC(XkbInitKeyboardDeviceStruct)
    SYMFUNC(XkbSetRulesDflts)
    SYMVAR(XkbDfltRepeatDelay)
    SYMVAR(XkbDfltRepeatInterval)
#endif

#ifdef XINPUT
    /* Xi */
    /* exevents.c */
    SYMFUNC(InitValuatorAxisStruct)
    SYMFUNC(InitProximityClassDeviceStruct)
    /* extinit.c */
    SYMFUNC(AssignTypeAndName)
#endif

    /* xf86DGA.c */
    /* XXX This is exported from the DDX, not DIX. */
    SYMVAR(XDGAEventBase)

    /* librender.a */
#ifdef RENDER
    /* picture.c */
    SYMFUNC(PictureInit)
    SYMFUNC(PictureTransformPoint)
    SYMFUNC(PictureTransformPoint3d)
    SYMFUNC(PictureGetSubpixelOrder)
    SYMFUNC(PictureSetSubpixelOrder)
    SYMVAR(PictureScreenPrivateIndex)
    /* mipict.c */
    SYMFUNC(miPictureInit)
    SYMFUNC(miComputeCompositeRegion)
    /* miglyph.c */
    SYMFUNC(miGlyphs)
    /* mirect.c */
    SYMFUNC(miCompositeRects)
    /* filter.c */
    SYMFUNC(PictureAddFilter)
    SYMFUNC(PictureSetFilterAlias)
    /* renderedge.c */
    SYMFUNC(RenderSampleCeilY)
    SYMFUNC(RenderSampleFloorY)
    SYMFUNC(RenderEdgeStep)
    SYMFUNC(RenderEdgeInit)
    SYMFUNC(RenderLineFixedEdgeInit)
#endif

    {0, 0}
};
