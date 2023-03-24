/* poppler-annotation.h: qt interface to poppler
 * Copyright (C) 2006-2008, 2012, 2013, 2018-2022 Albert Astals Cid <aacid@kde.org>
 * Copyright (C) 2006, 2008 Pino Toscano <pino@kde.org>
 * Copyright (C) 2007, Brad Hards <bradh@frogmouth.net>
 * Copyright (C) 2010, Philip Lorenz <lorenzph+freedesktop@gmail.com>
 * Copyright (C) 2012, 2015, Tobias Koenig <tobias.koenig@kdab.com>
 * Copyright (C) 2012, Guillermo A. Amaral B. <gamaral@kde.org>
 * Copyright (C) 2012, 2013 Fabio D'Urso <fabiodurso@hotmail.it>
 * Copyright (C) 2013, Anthony Granger <grangeranthony@gmail.com>
 * Copyright (C) 2018, Dileep Sankhla <sankhla.dileep96@gmail.com>
 * Copyright (C) 2020, Katarina Behrens <Katarina.Behrens@cib.de>
 * Copyright (C) 2020, Klarälvdalens Datakonsult AB, a KDAB Group company, <info@kdab.com>. Work sponsored by Technische Universität Dresden
 * Copyright (C) 2021, Mahmoud Ahmed Khalil <mahmoudkhalil11@gmail.com>
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
 
#ifndef _POPPLER_ANNOTATION_H_
#define _POPPLER_ANNOTATION_H_
 
#include <QtCore/QDateTime>
#include <QtCore/QSharedDataPointer>
#include <QtCore/QLinkedList>
#include <QtCore/QList>
#include <QtCore/QPointF>
#include <QtCore/QRectF>
#include <QtCore/QScopedPointer>
#include <QtCore/QVector>
#include <QtGui/QColor>
#include <QtGui/QFont>
#include <QtXml/QDomDocument>
#include "poppler-export.h"
 
#include <memory>
 
namespace Poppler {
 
class Annotation;
class AnnotationPrivate;
class AnnotationAppearancePrivate;
class TextAnnotationPrivate;
class LineAnnotationPrivate;
class GeomAnnotationPrivate;
class HighlightAnnotationPrivate;
class StampAnnotationPrivate;
class InkAnnotationPrivate;
class LinkAnnotationPrivate;
class CaretAnnotationPrivate;
class FileAttachmentAnnotationPrivate;
class SoundAnnotationPrivate;
class MovieAnnotationPrivate;
class ScreenAnnotationPrivate;
class WidgetAnnotationPrivate;
class RichMediaAnnotationPrivate;
class EmbeddedFile;
class Link;
class SoundObject;
class MovieObject;
class LinkRendition;
class Page;
 
class POPPLER_QT5_EXPORT AnnotationUtils
{
public:
    Q_DECL_DEPRECATED static Annotation *createAnnotation(const QDomElement &annElement);
 
    Q_DECL_DEPRECATED static void storeAnnotation(const Annotation *ann, QDomElement &annElement, QDomDocument &document);
 
    Q_DECL_DEPRECATED static QDomElement findChildElement(const QDomNode &parentNode, const QString &name);
};
 
class POPPLER_QT5_EXPORT AnnotationAppearance
{
    friend class Annotation;
 
public:
    explicit AnnotationAppearance(AnnotationAppearancePrivate *annotationAppearancePrivate);
    ~AnnotationAppearance();
 
private:
    AnnotationAppearancePrivate *d;
    Q_DISABLE_COPY(AnnotationAppearance)
};
 
class POPPLER_QT5_EXPORT Annotation
{
    friend class AnnotationUtils;
    friend class LinkMovie;
    friend class LinkRendition;
 
public:
    // enum definitions
    // WARNING!!! oKular uses that very same values so if you change them notify the author!
    enum SubType
    {
        AText = 1, 
        ALine = 2, 
        AGeom = 3, 
        AHighlight = 4, 
        AStamp = 5, 
        AInk = 6, 
        ALink = 7, 
        ACaret = 8, 
        AFileAttachment = 9, 
        ASound = 10, 
        AMovie = 11, 
        AScreen = 12, 
        AWidget = 13, 
        ARichMedia = 14, 
        A_BASE = 0
    };
 
    // NOTE: Only flags that are known to work are documented
    enum Flag
    {
        Hidden = 1, 
        FixedSize = 2,
        FixedRotation = 4, 
        DenyPrint = 8, 
        DenyWrite = 16,
        DenyDelete = 32,
        ToggleHidingOnMouse = 64,
        External = 128
    };
 
    enum LineStyle
    {
        Solid = 1,
        Dashed = 2,
        Beveled = 4,
        Inset = 8,
        Underline = 16
    };
    enum LineEffect
    {
        NoEffect = 1,
        Cloudy = 2
    };
    enum RevScope
    {
        Root = 0 ,
        Reply = 1,
        Group = 2,
        Delete = 4
    };
    enum RevType
    {
        None = 1,
        Marked = 2,
        Unmarked = 4,
        Accepted = 8,
        Rejected = 16,
        Cancelled = 32,
        Completed = 64
    };
 
    QString author() const;
    void setAuthor(const QString &author);
 
    QString contents() const;
    void setContents(const QString &contents);
 
    QString uniqueName() const;
    void setUniqueName(const QString &uniqueName);
 
    QDateTime modificationDate() const;
    void setModificationDate(const QDateTime &date);
 
    QDateTime creationDate() const;
    void setCreationDate(const QDateTime &date);
 
    int flags() const;
    void setFlags(int flags);
 
    QRectF boundary() const;
    void setBoundary(const QRectF &boundary);
 
    class POPPLER_QT5_EXPORT Style
    {
    public:
        Style();
        Style(const Style &other);
        Style &operator=(const Style &other);
        ~Style();
 
        // appearance properties
        QColor color() const; // black
        void setColor(const QColor &color);
        double opacity() const; // 1.0
        void setOpacity(double opacity);
 
        // pen properties
        double width() const; // 1.0
        void setWidth(double width);
        LineStyle lineStyle() const; // LineStyle::Solid
        void setLineStyle(LineStyle style);
        double xCorners() const; // 0.0
        void setXCorners(double radius);
        double yCorners() const; // 0.0
        void setYCorners(double radius);
        const QVector<double> &dashArray() const; // [ 3 ]
        void setDashArray(const QVector<double> &array);
 
        // pen effects
        LineEffect lineEffect() const; // LineEffect::NoEffect
        void setLineEffect(LineEffect effect);
        double effectIntensity() const; // 1.0
        void setEffectIntensity(double intens);
 
    private:
        class Private;
        QSharedDataPointer<Private> d;
    };
 
    Style style() const;
    void setStyle(const Style &style);
 
    class POPPLER_QT5_EXPORT Popup
    {
    public:
        Popup();
        Popup(const Popup &other);
        Popup &operator=(const Popup &other);
        ~Popup();
 
        // window state (Hidden, FixedRotation, Deny* flags allowed)
        int flags() const; // -1 (never initialized) -> 0 (if inited and shown)
        void setFlags(int flags);
 
        // geometric properties
        QRectF geometry() const; // no default
        void setGeometry(const QRectF &geom);
 
        // window contents/override properties
        QString title() const; // '' text in the titlebar (overrides author)
        void setTitle(const QString &title);
        QString summary() const; // '' short description (displayed if not empty)
        void setSummary(const QString &summary);
        QString text() const; // '' text for the window (overrides annot->contents)
        void setText(const QString &text);
 
    private:
        class Private;
        QSharedDataPointer<Private> d;
    };
 
    Popup popup() const;
    void setPopup(const Popup &popup);
 
    RevScope revisionScope() const; // Root
 
    RevType revisionType() const; // None
 
    QList<Annotation *> revisions() const;
 
    virtual SubType subType() const = 0;
 
    std::unique_ptr<AnnotationAppearance> annotationAppearance() const;
 
    void setAnnotationAppearance(const AnnotationAppearance &annotationAppearance);
 
    virtual ~Annotation();
 
    enum AdditionalActionType
    {
        CursorEnteringAction, 
        CursorLeavingAction, 
        MousePressedAction, 
        MouseReleasedAction, 
        FocusInAction, 
        FocusOutAction, 
        PageOpeningAction, 
        PageClosingAction, 
        PageVisibleAction, 
        PageInvisibleAction 
    };
 
protected:
    explicit Annotation(AnnotationPrivate &dd);
    Annotation(AnnotationPrivate &dd, const QDomNode &annNode);
    void storeBaseAnnotationProperties(QDomNode &annNode, QDomDocument &document) const;
    Q_DECLARE_PRIVATE(Annotation)
    QExplicitlySharedDataPointer<AnnotationPrivate> d_ptr;
 
private:
    virtual void store(QDomNode &parentNode, QDomDocument &document) const = 0;
    Q_DISABLE_COPY(Annotation)
};
 
class POPPLER_QT5_EXPORT TextAnnotation : public Annotation
{
    friend class AnnotationUtils;
    friend class AnnotationPrivate;
 
public:
    // local enums
    enum TextType
    {
        Linked,
        InPlace
    };
    enum InplaceIntent
    {
        Unknown,
        Callout,
        TypeWriter
    };
 
    explicit TextAnnotation(TextType type);
    ~TextAnnotation() override;
    SubType subType() const override;
 
    TextType textType() const;
 
    QString textIcon() const;
 
    void setTextIcon(const QString &icon);
 
    QFont textFont() const;
    void setTextFont(const QFont &font);
    QColor textColor() const;
    void setTextColor(const QColor &color);
 
    // 0:left, 1:center, 2:right
    int inplaceAlign() const;
    void setInplaceAlign(int align);
 
    QPointF calloutPoint(int id) const;
    QVector<QPointF> calloutPoints() const;
    void setCalloutPoints(const QVector<QPointF> &points);
 
    InplaceIntent inplaceIntent() const;
    void setInplaceIntent(InplaceIntent intent);
 
private:
    explicit TextAnnotation(const QDomNode &node);
    explicit TextAnnotation(TextAnnotationPrivate &dd);
    void store(QDomNode &parentNode, QDomDocument &document) const override;
    void setTextType(TextType type);
    Q_DECLARE_PRIVATE(TextAnnotation)
    Q_DISABLE_COPY(TextAnnotation)
};
 
class POPPLER_QT5_EXPORT LineAnnotation : public Annotation
{
    friend class AnnotationUtils;
    friend class AnnotationPrivate;
 
public:
    // local enums
    enum LineType
    {
        StraightLine,
        Polyline
    };
    enum TermStyle
    {
        Square,
        Circle,
        Diamond,
        OpenArrow,
        ClosedArrow,
        None,
        Butt,
        ROpenArrow,
        RClosedArrow,
        Slash
    };
    enum LineIntent
    {
        Unknown,
        Arrow,
        Dimension,
        PolygonCloud
    };
 
    explicit LineAnnotation(LineType type);
    ~LineAnnotation() override;
    SubType subType() const override;
 
    LineType lineType() const;
 
    QLinkedList<QPointF> linePoints() const;
    void setLinePoints(const QLinkedList<QPointF> &points);
 
    TermStyle lineStartStyle() const;
    void setLineStartStyle(TermStyle style);
 
    TermStyle lineEndStyle() const;
    void setLineEndStyle(TermStyle style);
 
    bool isLineClosed() const;
    void setLineClosed(bool closed);
 
    QColor lineInnerColor() const;
    void setLineInnerColor(const QColor &color);
 
    double lineLeadingForwardPoint() const;
    void setLineLeadingForwardPoint(double point);
 
    double lineLeadingBackPoint() const;
    void setLineLeadingBackPoint(double point);
 
    bool lineShowCaption() const;
    void setLineShowCaption(bool show);
 
    LineIntent lineIntent() const;
    void setLineIntent(LineIntent intent);
 
private:
    explicit LineAnnotation(const QDomNode &node);
    explicit LineAnnotation(LineAnnotationPrivate &dd);
    void store(QDomNode &parentNode, QDomDocument &document) const override;
    void setLineType(LineType type);
    Q_DECLARE_PRIVATE(LineAnnotation)
    Q_DISABLE_COPY(LineAnnotation)
};
 
class POPPLER_QT5_EXPORT GeomAnnotation : public Annotation
{
    friend class AnnotationUtils;
    friend class AnnotationPrivate;
 
public:
    GeomAnnotation();
    ~GeomAnnotation() override;
    SubType subType() const override;
 
    // common enums
    enum GeomType
    {
        InscribedSquare,
        InscribedCircle
    };
 
    GeomType geomType() const;
    void setGeomType(GeomType type);
 
    QColor geomInnerColor() const;
    void setGeomInnerColor(const QColor &color);
 
private:
    explicit GeomAnnotation(const QDomNode &node);
    explicit GeomAnnotation(GeomAnnotationPrivate &dd);
    void store(QDomNode &parentNode, QDomDocument &document) const override;
    Q_DECLARE_PRIVATE(GeomAnnotation)
    Q_DISABLE_COPY(GeomAnnotation)
};
 
class POPPLER_QT5_EXPORT HighlightAnnotation : public Annotation
{
    friend class AnnotationUtils;
    friend class AnnotationPrivate;
 
public:
    HighlightAnnotation();
    ~HighlightAnnotation() override;
    SubType subType() const override;
 
    enum HighlightType
    {
        Highlight, 
        Squiggly, 
        Underline, 
        StrikeOut 
    };
 
    struct Quad
    {
        QPointF points[4]; // 8 valid coords
        bool capStart; // false (vtx 1-4) [K]
        bool capEnd; // false (vtx 2-3) [K]
        double feather; // 0.1 (in range 0..1) [K]
    };
 
    HighlightType highlightType() const;
 
    void setHighlightType(HighlightType type);
 
    QList<Quad> highlightQuads() const;
 
    void setHighlightQuads(const QList<Quad> &quads);
 
private:
    explicit HighlightAnnotation(const QDomNode &node);
    explicit HighlightAnnotation(HighlightAnnotationPrivate &dd);
    void store(QDomNode &parentNode, QDomDocument &document) const override;
    Q_DECLARE_PRIVATE(HighlightAnnotation)
    Q_DISABLE_COPY(HighlightAnnotation)
};
 
class POPPLER_QT5_EXPORT StampAnnotation : public Annotation
{
    friend class AnnotationUtils;
    friend class AnnotationPrivate;
 
public:
    StampAnnotation();
    ~StampAnnotation() override;
    SubType subType() const override;
 
    QString stampIconName() const;
 
    void setStampIconName(const QString &name);
 
    void setStampCustomImage(const QImage &image);
 
private:
    explicit StampAnnotation(const QDomNode &node);
    explicit StampAnnotation(StampAnnotationPrivate &dd);
    void store(QDomNode &parentNode, QDomDocument &document) const override;
    Q_DECLARE_PRIVATE(StampAnnotation)
    Q_DISABLE_COPY(StampAnnotation)
};
 
class POPPLER_QT5_EXPORT InkAnnotation : public Annotation
{
    friend class AnnotationUtils;
    friend class AnnotationPrivate;
 
public:
    InkAnnotation();
    ~InkAnnotation() override;
    SubType subType() const override;
 
    QList<QLinkedList<QPointF>> inkPaths() const;
    void setInkPaths(const QList<QLinkedList<QPointF>> &paths);
 
private:
    explicit InkAnnotation(const QDomNode &node);
    void store(QDomNode &parentNode, QDomDocument &document) const override;
    explicit InkAnnotation(InkAnnotationPrivate &dd);
    Q_DECLARE_PRIVATE(InkAnnotation)
    Q_DISABLE_COPY(InkAnnotation)
};
 
class POPPLER_QT5_EXPORT LinkAnnotation : public Annotation
{
    friend class AnnotationUtils;
    friend class AnnotationPrivate;
 
public:
    ~LinkAnnotation() override;
    SubType subType() const override;
 
    // local enums
    enum HighlightMode
    {
        None,
        Invert,
        Outline,
        Push
    };
 
    Link *linkDestination() const;
    void setLinkDestination(Link *link);
 
    HighlightMode linkHighlightMode() const;
    void setLinkHighlightMode(HighlightMode mode);
 
    QPointF linkRegionPoint(int id) const;
    // TODO Next ABI break, remove ref from point
    void setLinkRegionPoint(int id, const QPointF &point);
 
private:
    LinkAnnotation();
    explicit LinkAnnotation(const QDomNode &node);
    explicit LinkAnnotation(LinkAnnotationPrivate &dd);
    void store(QDomNode &parentNode, QDomDocument &document) const override;
    Q_DECLARE_PRIVATE(LinkAnnotation)
    Q_DISABLE_COPY(LinkAnnotation)
};
 
class POPPLER_QT5_EXPORT CaretAnnotation : public Annotation
{
    friend class AnnotationUtils;
    friend class AnnotationPrivate;
 
public:
    CaretAnnotation();
    ~CaretAnnotation() override;
    SubType subType() const override;
 
    enum CaretSymbol
    {
        None,
        P
    };
 
    CaretSymbol caretSymbol() const;
    void setCaretSymbol(CaretSymbol symbol);
 
private:
    explicit CaretAnnotation(const QDomNode &node);
    explicit CaretAnnotation(CaretAnnotationPrivate &dd);
    void store(QDomNode &parentNode, QDomDocument &document) const override;
    Q_DECLARE_PRIVATE(CaretAnnotation)
    Q_DISABLE_COPY(CaretAnnotation)
};
 
class POPPLER_QT5_EXPORT FileAttachmentAnnotation : public Annotation
{
    friend class AnnotationPrivate;
 
public:
    ~FileAttachmentAnnotation() override;
    SubType subType() const override;
 
    QString fileIconName() const;
    void setFileIconName(const QString &icon);
 
    EmbeddedFile *embeddedFile() const;
    void setEmbeddedFile(EmbeddedFile *ef);
 
private:
    FileAttachmentAnnotation();
    explicit FileAttachmentAnnotation(const QDomNode &node);
    explicit FileAttachmentAnnotation(FileAttachmentAnnotationPrivate &dd);
    void store(QDomNode &parentNode, QDomDocument &document) const override;
    Q_DECLARE_PRIVATE(FileAttachmentAnnotation)
    Q_DISABLE_COPY(FileAttachmentAnnotation)
};
 
class POPPLER_QT5_EXPORT SoundAnnotation : public Annotation
{
    friend class AnnotationPrivate;
 
public:
    ~SoundAnnotation() override;
    SubType subType() const override;
 
    QString soundIconName() const;
    void setSoundIconName(const QString &icon);
 
    SoundObject *sound() const;
    void setSound(SoundObject *s);
 
private:
    SoundAnnotation();
    explicit SoundAnnotation(const QDomNode &node);
    explicit SoundAnnotation(SoundAnnotationPrivate &dd);
    void store(QDomNode &parentNode, QDomDocument &document) const override;
    Q_DECLARE_PRIVATE(SoundAnnotation)
    Q_DISABLE_COPY(SoundAnnotation)
};
 
class POPPLER_QT5_EXPORT MovieAnnotation : public Annotation
{
    friend class AnnotationPrivate;
 
public:
    ~MovieAnnotation() override;
    SubType subType() const override;
 
    MovieObject *movie() const;
    void setMovie(MovieObject *movie);
 
    QString movieTitle() const;
    void setMovieTitle(const QString &title);
 
private:
    MovieAnnotation();
    explicit MovieAnnotation(const QDomNode &node);
    explicit MovieAnnotation(MovieAnnotationPrivate &dd);
    void store(QDomNode &parentNode, QDomDocument &document) const override;
    Q_DECLARE_PRIVATE(MovieAnnotation)
    Q_DISABLE_COPY(MovieAnnotation)
};
 
class POPPLER_QT5_EXPORT ScreenAnnotation : public Annotation
{
    friend class AnnotationPrivate;
 
public:
    ~ScreenAnnotation() override;
 
    SubType subType() const override;
 
    LinkRendition *action() const;
 
    void setAction(LinkRendition *action);
 
    QString screenTitle() const;
 
    void setScreenTitle(const QString &title);
 
    Link *additionalAction(AdditionalActionType type) const;
 
private:
    ScreenAnnotation();
    explicit ScreenAnnotation(ScreenAnnotationPrivate &dd);
    void store(QDomNode &parentNode, QDomDocument &document) const override; // stub
    Q_DECLARE_PRIVATE(ScreenAnnotation)
    Q_DISABLE_COPY(ScreenAnnotation)
};
 
class POPPLER_QT5_EXPORT WidgetAnnotation : public Annotation
{
    friend class AnnotationPrivate;
 
public:
    ~WidgetAnnotation() override;
 
    SubType subType() const override;
 
    Link *additionalAction(AdditionalActionType type) const;
 
private:
    WidgetAnnotation();
    explicit WidgetAnnotation(WidgetAnnotationPrivate &dd);
    void store(QDomNode &parentNode, QDomDocument &document) const override; // stub
    Q_DECLARE_PRIVATE(WidgetAnnotation)
    Q_DISABLE_COPY(WidgetAnnotation)
};
 
class POPPLER_QT5_EXPORT RichMediaAnnotation : public Annotation
{
    friend class AnnotationPrivate;
 
public:
    ~RichMediaAnnotation() override;
 
    SubType subType() const override;
 
    class POPPLER_QT5_EXPORT Params
    {
        friend class AnnotationPrivate;
 
    public:
        Params();
        ~Params();
 
        QString flashVars() const;
 
    private:
        void setFlashVars(const QString &flashVars);
 
        class Private;
        QScopedPointer<Private> d;
    };
 
    class POPPLER_QT5_EXPORT Instance
    {
        friend class AnnotationPrivate;
 
    public:
        enum Type
        {
            Type3D, 
            TypeFlash, 
            TypeSound, 
            TypeVideo 
        };
 
        Instance();
        ~Instance();
 
        Type type() const;
 
        RichMediaAnnotation::Params *params() const;
 
    private:
        void setType(Type type);
        void setParams(RichMediaAnnotation::Params *params);
 
        class Private;
        QScopedPointer<Private> d;
    };
 
    class POPPLER_QT5_EXPORT Configuration
    {
        friend class AnnotationPrivate;
 
    public:
        enum Type
        {
            Type3D, 
            TypeFlash, 
            TypeSound, 
            TypeVideo 
        };
 
        Configuration();
        ~Configuration();
 
        Type type() const;
 
        QString name() const;
 
        QList<RichMediaAnnotation::Instance *> instances() const;
 
    private:
        void setType(Type type);
        void setName(const QString &name);
        void setInstances(const QList<RichMediaAnnotation::Instance *> &instances);
 
        class Private;
        QScopedPointer<Private> d;
    };
 
    class POPPLER_QT5_EXPORT Asset
    {
        friend class AnnotationPrivate;
 
    public:
        Asset();
        ~Asset();
 
        QString name() const;
 
        EmbeddedFile *embeddedFile() const;
 
    private:
        void setName(const QString &name);
        void setEmbeddedFile(EmbeddedFile *embeddedFile);
 
        class Private;
        QScopedPointer<Private> d;
    };
 
    class POPPLER_QT5_EXPORT Content
    {
        friend class AnnotationPrivate;
 
    public:
        Content();
        ~Content();
 
        QList<RichMediaAnnotation::Configuration *> configurations() const;
 
        QList<RichMediaAnnotation::Asset *> assets() const;
 
    private:
        void setConfigurations(const QList<RichMediaAnnotation::Configuration *> &configurations);
        void setAssets(const QList<RichMediaAnnotation::Asset *> &assets);
 
        class Private;
        QScopedPointer<Private> d;
    };
 
    class POPPLER_QT5_EXPORT Activation
    {
        friend class AnnotationPrivate;
 
    public:
        enum Condition
        {
            PageOpened, 
            PageVisible, 
            UserAction 
        };
 
        Activation();
        ~Activation();
 
        Condition condition() const;
 
    private:
        void setCondition(Condition condition);
 
        class Private;
        QScopedPointer<Private> d;
    };
 
    class POPPLER_QT5_EXPORT Deactivation
    {
        friend class AnnotationPrivate;
 
    public:
        enum Condition
        {
            PageClosed, 
            PageInvisible, 
            UserAction 
        };
 
        Deactivation();
        ~Deactivation();
 
        Condition condition() const;
 
    private:
        void setCondition(Condition condition);
 
        class Private;
        QScopedPointer<Private> d;
    };
 
    class POPPLER_QT5_EXPORT Settings
    {
        friend class AnnotationPrivate;
 
    public:
        Settings();
        ~Settings();
 
        RichMediaAnnotation::Activation *activation() const;
 
        RichMediaAnnotation::Deactivation *deactivation() const;
 
    private:
        void setActivation(RichMediaAnnotation::Activation *activation);
        void setDeactivation(RichMediaAnnotation::Deactivation *deactivation);
 
        class Private;
        QScopedPointer<Private> d;
    };
 
    RichMediaAnnotation::Settings *settings() const;
 
    RichMediaAnnotation::Content *content() const;
 
private:
    void setSettings(RichMediaAnnotation::Settings *settings);
    void setContent(RichMediaAnnotation::Content *content);
 
    RichMediaAnnotation();
    explicit RichMediaAnnotation(const QDomNode &node);
    explicit RichMediaAnnotation(RichMediaAnnotationPrivate &dd);
    void store(QDomNode &parentNode, QDomDocument &document) const override;
    Q_DECLARE_PRIVATE(RichMediaAnnotation)
    Q_DISABLE_COPY(RichMediaAnnotation)
};
 
}
 
#endif

