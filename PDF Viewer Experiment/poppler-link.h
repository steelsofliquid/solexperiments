/* poppler-link.h: qt interface to poppler
 * Copyright (C) 2006, 2013, 2016, 2018, 2019, 2021, 2022, Albert Astals Cid <aacid@kde.org>
 * Copyright (C) 2007-2008, 2010, Pino Toscano <pino@kde.org>
 * Copyright (C) 2010, 2012, Guillermo Amaral <gamaral@kdab.com>
 * Copyright (C) 2012, Tobias Koenig <tokoe@kdab.com>
 * Copyright (C) 2013, Anthony Granger <grangeranthony@gmail.com>
 * Copyright (C) 2018 Intevation GmbH <intevation@intevation.de>
 * Copyright (C) 2020 Oliver Sander <oliver.sander@tu-dresden.de>
 * Adapting code from
 *   Copyright (C) 2004 by Enrico Ros <eros.kde@email.it>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston, MA 02110-1301, USA.
 */
 
#ifndef _POPPLER_LINK_H_
#define _POPPLER_LINK_H_
 
#include <QtCore/QString>
#include <QtCore/QRectF>
#include <QtCore/QSharedDataPointer>
#include <QtCore/QVector>
#include "poppler-export.h"
 
struct Ref;
class MediaRendition;
 
namespace Poppler {
 
class LinkPrivate;
class LinkGotoPrivate;
class LinkExecutePrivate;
class LinkBrowsePrivate;
class LinkActionPrivate;
class LinkSoundPrivate;
class LinkJavaScriptPrivate;
class LinkMoviePrivate;
class LinkDestinationData;
class LinkDestinationPrivate;
class LinkRenditionPrivate;
class LinkOCGStatePrivate;
class LinkHidePrivate;
class MediaRendition;
class MovieAnnotation;
class ScreenAnnotation;
class SoundObject;
 
class POPPLER_QT5_EXPORT LinkDestination
{
public:
    enum Kind
    {
        destXYZ = 1,
        destFit = 2,
        destFitH = 3,
        destFitV = 4,
        destFitR = 5,
        destFitB = 6,
        destFitBH = 7,
        destFitBV = 8
    };
 
    explicit LinkDestination(const LinkDestinationData &data);
    explicit LinkDestination(const QString &description);
 
    LinkDestination(const LinkDestination &other);
    ~LinkDestination();
 
    // Accessors.
    Kind kind() const;
    int pageNumber() const;
    double left() const;
    double bottom() const;
    double right() const;
    double top() const;
    double zoom() const;
    bool isChangeLeft() const;
    bool isChangeTop() const;
    bool isChangeZoom() const;
 
    QString toString() const;
 
    QString destinationName() const;
 
    LinkDestination &operator=(const LinkDestination &other);
 
private:
    QSharedDataPointer<LinkDestinationPrivate> d;
};
 
class POPPLER_QT5_EXPORT Link
{
public:
    explicit Link(const QRectF &linkArea);
 
    enum LinkType
    {
        None, 
        Goto, 
        Execute, 
        Browse, 
        Action, 
        Sound, 
        Movie, 
        Rendition, 
        JavaScript, 
        OCGState, 
        Hide, 
    };
 
    virtual LinkType linkType() const;
 
    virtual ~Link();
 
    QRectF linkArea() const;
 
    QVector<Link *> nextLinks() const;
 
protected:
    explicit Link(LinkPrivate &dd);
    Q_DECLARE_PRIVATE(Link)
    LinkPrivate *d_ptr;
 
private:
    Q_DISABLE_COPY(Link)
};
 
class POPPLER_QT5_EXPORT LinkGoto : public Link
{
public:
    // TODO Next ABI break, make extFileName const &
    LinkGoto(const QRectF &linkArea, QString extFileName, const LinkDestination &destination);
    ~LinkGoto() override;
 
    bool isExternal() const;
    // query for goto parameters
    QString fileName() const;
    LinkDestination destination() const;
    LinkType linkType() const override;
 
private:
    Q_DECLARE_PRIVATE(LinkGoto)
    Q_DISABLE_COPY(LinkGoto)
};
 
class POPPLER_QT5_EXPORT LinkExecute : public Link
{
public:
    QString fileName() const;
    QString parameters() const;
 
    LinkExecute(const QRectF &linkArea, const QString &file, const QString &params);
    ~LinkExecute() override;
    LinkType linkType() const override;
 
private:
    Q_DECLARE_PRIVATE(LinkExecute)
    Q_DISABLE_COPY(LinkExecute)
};
 
class POPPLER_QT5_EXPORT LinkBrowse : public Link
{
public:
    QString url() const;
 
    LinkBrowse(const QRectF &linkArea, const QString &url);
    ~LinkBrowse() override;
    LinkType linkType() const override;
 
private:
    Q_DECLARE_PRIVATE(LinkBrowse)
    Q_DISABLE_COPY(LinkBrowse)
};
 
class POPPLER_QT5_EXPORT LinkAction : public Link
{
public:
    enum ActionType
    {
        PageFirst = 1,
        PagePrev = 2,
        PageNext = 3,
        PageLast = 4,
        HistoryBack = 5,
        HistoryForward = 6,
        Quit = 7,
        Presentation = 8,
        EndPresentation = 9,
        Find = 10,
        GoToPage = 11,
        Close = 12,
        Print = 13, 
        SaveAs = 14 
    };
 
    ActionType actionType() const;
 
    LinkAction(const QRectF &linkArea, ActionType actionType);
    ~LinkAction() override;
    LinkType linkType() const override;
 
private:
    Q_DECLARE_PRIVATE(LinkAction)
    Q_DISABLE_COPY(LinkAction)
};
 
class POPPLER_QT5_EXPORT LinkSound : public Link
{
public:
    // create a Link_Sound
    LinkSound(const QRectF &linkArea, double volume, bool sync, bool repeat, bool mix, SoundObject *sound);
    ~LinkSound() override;
 
    LinkType linkType() const override;
 
    double volume() const;
    bool synchronous() const;
    bool repeat() const;
    bool mix() const;
    SoundObject *sound() const;
 
private:
    Q_DECLARE_PRIVATE(LinkSound)
    Q_DISABLE_COPY(LinkSound)
};
 
class POPPLER_QT5_EXPORT LinkRendition : public Link
{
public:
    enum RenditionAction
    {
        NoRendition,
        PlayRendition,
        StopRendition,
        PauseRendition,
        ResumeRendition
    };
 
    // TODO Next ABI break, remove & from annotationReference
    LinkRendition(const QRectF &linkArea, ::MediaRendition *rendition, int operation, const QString &script, const Ref &annotationReference);
 
    ~LinkRendition() override;
 
    LinkType linkType() const override;
 
    MediaRendition *rendition() const;
 
    RenditionAction action() const;
 
    QString script() const;
 
    bool isReferencedAnnotation(const ScreenAnnotation *annotation) const;
 
private:
    Q_DECLARE_PRIVATE(LinkRendition)
    Q_DISABLE_COPY(LinkRendition)
};
 
class POPPLER_QT5_EXPORT LinkJavaScript : public Link
{
public:
    LinkJavaScript(const QRectF &linkArea, const QString &js);
    ~LinkJavaScript() override;
 
    LinkType linkType() const override;
 
    QString script() const;
 
private:
    Q_DECLARE_PRIVATE(LinkJavaScript)
    Q_DISABLE_COPY(LinkJavaScript)
};
 
class POPPLER_QT5_EXPORT LinkMovie : public Link
{
public:
    enum Operation
    {
        Play,
        Stop,
        Pause,
        Resume
    };
 
    // TODO Next ABI break, remove & from annotationReference
    LinkMovie(const QRectF &linkArea, Operation operation, const QString &annotationTitle, const Ref &annotationReference);
    ~LinkMovie() override;
    LinkType linkType() const override;
    Operation operation() const;
    bool isReferencedAnnotation(const MovieAnnotation *annotation) const;
 
private:
    Q_DECLARE_PRIVATE(LinkMovie)
    Q_DISABLE_COPY(LinkMovie)
};
 
class POPPLER_QT5_EXPORT LinkOCGState : public Link
{
    friend class OptContentModel;
 
public:
    explicit LinkOCGState(LinkOCGStatePrivate *ocgp);
    ~LinkOCGState() override;
 
    LinkType linkType() const override;
 
private:
    Q_DECLARE_PRIVATE(LinkOCGState)
    Q_DISABLE_COPY(LinkOCGState)
};
 
class POPPLER_QT5_EXPORT LinkHide : public Link
{
public:
    explicit LinkHide(LinkHidePrivate *lhidep);
    ~LinkHide() override;
 
    LinkType linkType() const override;
 
    QVector<QString> targets() const;
 
    bool isShowAction() const;
 
private:
    Q_DECLARE_PRIVATE(LinkHide)
    Q_DISABLE_COPY(LinkHide)
};
 
}
 
#endif

