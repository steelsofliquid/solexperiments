/* poppler-qt.h: qt interface to poppler
 * Copyright (C) 2005, Net Integration Technologies, Inc.
 * Copyright (C) 2005, 2007, Brad Hards <bradh@frogmouth.net>
 * Copyright (C) 2005-2015, 2017-2022, Albert Astals Cid <aacid@kde.org>
 * Copyright (C) 2005, Stefan Kebekus <stefan.kebekus@math.uni-koeln.de>
 * Copyright (C) 2006-2011, Pino Toscano <pino@kde.org>
 * Copyright (C) 2009 Shawn Rutledge <shawn.t.rutledge@gmail.com>
 * Copyright (C) 2010 Suzuki Toshiya <mpsuzuki@hiroshima-u.ac.jp>
 * Copyright (C) 2010 Matthias Fauconneau <matthias.fauconneau@gmail.com>
 * Copyright (C) 2011 Andreas Hartmetz <ahartmetz@gmail.com>
 * Copyright (C) 2011 Glad Deschrijver <glad.deschrijver@gmail.com>
 * Copyright (C) 2012, Guillermo A. Amaral B. <gamaral@kde.org>
 * Copyright (C) 2012, Fabio D'Urso <fabiodurso@hotmail.it>
 * Copyright (C) 2012, Tobias Koenig <tobias.koenig@kdab.com>
 * Copyright (C) 2012, 2014, 2015, 2018, 2019 Adam Reichold <adamreichold@myopera.com>
 * Copyright (C) 2012, 2013 Thomas Freitag <Thomas.Freitag@alfa.de>
 * Copyright (C) 2013 Anthony Granger <grangeranthony@gmail.com>
 * Copyright (C) 2016 Jakub Alba <jakubalba@gmail.com>
 * Copyright (C) 2017, 2020, 2021 Oliver Sander <oliver.sander@tu-dresden.de>
 * Copyright (C) 2017, 2018 Klarälvdalens Datakonsult AB, a KDAB Group company, <info@kdab.com>. Work sponsored by the LiMux project of the city of Munich
 * Copyright (C) 2018, 2021 Nelson Benítez León <nbenitezl@gmail.com>
 * Copyright (C) 2019 Jan Grulich <jgrulich@redhat.com>
 * Copyright (C) 2019 Alexander Volkov <a.volkov@rusbitech.ru>
 * Copyright (C) 2020 Philipp Knechtges <philipp-dev@knechtges.com>
 * Copyright (C) 2020 Katarina Behrens <Katarina.Behrens@cib.de>
 * Copyright (C) 2020 Thorsten Behrens <Thorsten.Behrens@CIB.de>
 * Copyright (C) 2020 Klarälvdalens Datakonsult AB, a KDAB Group company, <info@kdab.com>. Work sponsored by Technische Universität Dresden
 * Copyright (C) 2021 Klarälvdalens Datakonsult AB, a KDAB Group company, <info@kdab.com>.
 * Copyright (C) 2021 Mahmoud Khalil <mahmoudkhalil11@gmail.com>
 * Copyright (C) 2021 Georgiy Sgibnev <georgiy@sgibnev.com>. Work sponsored by lab50.net.
 * Copyright (C) 2022 Martin <martinbts@gmx.net>
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
 
#ifndef __POPPLER_QT_H__
#define __POPPLER_QT_H__
 
#include <functional>
 
#include "poppler-annotation.h"
#include "poppler-link.h"
#include "poppler-optcontent.h"
#include "poppler-page-transition.h"
 
#include <QtCore/QByteArray>
#include <QtCore/QDateTime>
#include <QtCore/QSet>
#include <QtXml/QDomDocument>
#include "poppler-export.h"
 
class EmbFile;
class Sound;
class AnnotMovie;
 
namespace Poppler {
 
class Document;
class DocumentData;
 
class PageData;
 
class FormField;
class FormFieldSignature;
 
class TextBoxData;
 
class PDFConverter;
class PSConverter;
 
struct OutlineItemData;
 
using PopplerDebugFunc = void (*)(const QString & /*message*/, const QVariant & /*closure*/);
 
POPPLER_QT5_EXPORT void setDebugErrorFunction(PopplerDebugFunc debugFunction, const QVariant &closure);
 
class POPPLER_QT5_EXPORT TextBox
{
    friend class Page;
 
public:
    TextBox(const QString &text, const QRectF &bBox);
    ~TextBox();
 
    QString text() const;
 
    QRectF boundingBox() const;
 
    TextBox *nextWord() const;
 
    QRectF charBoundingBox(int i) const;
 
    bool hasSpaceAfter() const;
 
private:
    Q_DISABLE_COPY(TextBox)
 
    TextBoxData *m_data;
};
 
class FontInfoData;
class POPPLER_QT5_EXPORT FontInfo
{
    friend class Document;
 
public:
    enum Type
    {
        unknown,
        Type1,
        Type1C,
        Type1COT,
        Type3,
        TrueType,
        TrueTypeOT,
        CIDType0,
        CIDType0C,
        CIDType0COT,
        CIDTrueType,
        CIDTrueTypeOT
    };
 
 
    FontInfo();
 
    explicit FontInfo(const FontInfoData &fid);
 
    FontInfo(const FontInfo &fi);
 
    ~FontInfo();
 
    QString name() const;
 
    QString substituteName() const;
 
    QString file() const;
 
    bool isEmbedded() const;
 
    bool isSubset() const;
 
    Type type() const;
 
    QString typeName() const;
 
    FontInfo &operator=(const FontInfo &fi);
 
private:
    FontInfoData *m_data;
};
 
class FontIteratorData;
class POPPLER_QT5_EXPORT FontIterator
{
    friend class Document;
    friend class DocumentData;
 
public:
    ~FontIterator();
 
    QList<FontInfo> next();
 
    bool hasNext() const;
 
    int currentPage() const;
 
private:
    Q_DISABLE_COPY(FontIterator)
    FontIterator(int, DocumentData *dd);
 
    FontIteratorData *d;
};
 
class EmbeddedFileData;
class POPPLER_QT5_EXPORT EmbeddedFile
{
    friend class DocumentData;
    friend class AnnotationPrivate;
 
public:
    explicit EmbeddedFile(EmbFile *embfile);
 
    ~EmbeddedFile();
 
    QString name() const;
 
    QString description() const;
 
    int size() const;
 
    QDateTime modDate() const;
 
    QDateTime createDate() const;
 
    QByteArray checksum() const;
 
    QString mimeType() const;
 
    QByteArray data();
 
    bool isValid() const;
 
    // QDataStream dataStream() const;
 
private:
    Q_DISABLE_COPY(EmbeddedFile)
    explicit EmbeddedFile(EmbeddedFileData &dd);
 
    EmbeddedFileData *m_embeddedFile;
};
 
class POPPLER_QT5_EXPORT Page
{
    friend class Document;
 
public:
    ~Page();
 
    enum Rotation
    {
        Rotate0 = 0, 
        Rotate90 = 1, 
        Rotate180 = 2, 
        Rotate270 = 3 
    };
 
    enum PageAction
    {
        Opening, 
        Closing 
    };
 
    enum TextLayout
    {
        PhysicalLayout, 
        RawOrderLayout 
    };
 
    enum PainterFlag
    {
        NoPainterFlags = 0x00000000, 
        DontSaveAndRestore = 0x00000001
    };
    Q_DECLARE_FLAGS(PainterFlags, PainterFlag)
 
    
    QImage renderToImage(double xres = 72.0, double yres = 72.0, int x = -1, int y = -1, int w = -1, int h = -1, Rotation rotate = Rotate0) const;
 
    using RenderToImagePartialUpdateFunc = void (*)(const QImage & /*image*/, const QVariant & /*closure*/);
 
    using ShouldRenderToImagePartialQueryFunc = bool (*)(const QVariant & /*closure*/);
 
    QImage renderToImage(double xres, double yres, int x, int y, int w, int h, Rotation rotate, RenderToImagePartialUpdateFunc partialUpdateCallback, ShouldRenderToImagePartialQueryFunc shouldDoPartialUpdateCallback,
                         const QVariant &payload) const;
 
    using ShouldAbortQueryFunc = bool (*)(const QVariant & /*closure*/);
 
    QImage renderToImage(double xres, double yres, int x, int y, int w, int h, Rotation rotate, RenderToImagePartialUpdateFunc partialUpdateCallback, ShouldRenderToImagePartialQueryFunc shouldDoPartialUpdateCallback,
                         ShouldAbortQueryFunc shouldAbortRenderCallback, const QVariant &payload) const;
 
    bool renderToPainter(QPainter *painter, double xres = 72.0, double yres = 72.0, int x = -1, int y = -1, int w = -1, int h = -1, Rotation rotate = Rotate0, PainterFlags flags = NoPainterFlags) const;
 
    QImage thumbnail() const;
 
    QString text(const QRectF &rect, TextLayout textLayout) const;
 
    QString text(const QRectF &rect) const;
 
    enum SearchDirection
    {
        FromTop, 
        NextResult, 
        PreviousResult 
    };
 
    enum SearchMode
    {
        CaseSensitive, 
        CaseInsensitive 
    };
 
    enum SearchFlag
    {
        NoSearchFlags = 0x00000000, 
        IgnoreCase = 0x00000001, 
        WholeWords = 0x00000002, 
        IgnoreDiacritics = 0x00000004, 
        AcrossLines = 0x00000008 
    };
    Q_DECLARE_FLAGS(SearchFlags, SearchFlag)
 
    
    Q_DECL_DEPRECATED bool search(const QString &text, double &rectLeft, double &rectTop, double &rectRight, double &rectBottom, SearchDirection direction, SearchMode caseSensitive, Rotation rotate = Rotate0) const;
 
    bool search(const QString &text, double &sLeft, double &sTop, double &sRight, double &sBottom, SearchDirection direction, SearchFlags flags = NoSearchFlags, Rotation rotate = Rotate0) const;
 
    Q_DECL_DEPRECATED QList<QRectF> search(const QString &text, SearchMode caseSensitive, Rotation rotate = Rotate0) const;
 
    QList<QRectF> search(const QString &text, SearchFlags flags = NoSearchFlags, Rotation rotate = Rotate0) const;
 
    QList<TextBox *> textList(Rotation rotate = Rotate0) const;
 
    QList<TextBox *> textList(Rotation rotate, ShouldAbortQueryFunc shouldAbortExtractionCallback, const QVariant &closure) const;
 
    QSizeF pageSizeF() const;
 
    QSize pageSize() const;
 
    PageTransition *transition() const;
 
    Link *action(PageAction act) const;
 
    enum Orientation
    {
        Landscape, 
        Portrait, 
        Seascape, 
        UpsideDown 
    };
 
    Orientation orientation() const;
 
    void defaultCTM(double *CTM, double dpiX, double dpiY, int rotate, bool upsideDown);
 
    QList<Link *> links() const;
 
    QList<Annotation *> annotations() const;
 
    QList<Annotation *> annotations(const QSet<Annotation::SubType> &subtypes) const;
 
    void addAnnotation(const Annotation *ann);
 
    void removeAnnotation(const Annotation *ann);
 
    QList<FormField *> formFields() const;
 
    double duration() const;
 
    QString label() const;
 
    int index() const;
 
private:
    Q_DISABLE_COPY(Page)
 
    Page(DocumentData *doc, int index);
    PageData *m_page;
};
 
class POPPLER_QT5_EXPORT OutlineItem
{
    friend class Document;
 
public:
    OutlineItem();
    ~OutlineItem();
 
    OutlineItem(const OutlineItem &other);
    OutlineItem &operator=(const OutlineItem &other);
 
    OutlineItem(OutlineItem &&other) noexcept;
    OutlineItem &operator=(OutlineItem &&other) noexcept;
 
    bool isNull() const;
 
    QString name() const;
 
    bool isOpen() const;
 
    QSharedPointer<const LinkDestination> destination() const;
 
    QString externalFileName() const;
 
    QString uri() const;
 
    bool hasChildren() const;
 
    QVector<OutlineItem> children() const;
 
private:
    explicit OutlineItem(OutlineItemData *data);
    OutlineItemData *m_data;
};
 
class POPPLER_QT5_EXPORT Document
{
    friend class Page;
    friend class DocumentData;
 
public:
    enum PageMode
    {
        UseNone, 
        UseOutlines, 
        UseThumbs, 
        FullScreen, 
        UseOC, 
        UseAttach 
    };
 
    enum PageLayout
    {
        NoLayout, 
        SinglePage, 
        OneColumn, 
        TwoColumnLeft, 
        TwoColumnRight, 
        TwoPageLeft, 
        TwoPageRight 
    };
 
    enum RenderBackend
    {
        SplashBackend, 
        ArthurBackend, 
        QPainterBackend = ArthurBackend 
    };
 
    enum RenderHint
    {
        Antialiasing = 0x00000001, 
        TextAntialiasing = 0x00000002, 
        TextHinting = 0x00000004, 
        TextSlightHinting = 0x00000008, 
        OverprintPreview = 0x00000010, 
        ThinLineSolid = 0x00000020, 
        ThinLineShape = 0x00000040, 
        IgnorePaperColor = 0x00000080, 
        HideAnnotations = 0x00000100 
    };
    Q_DECLARE_FLAGS(RenderHints, RenderHint)
 
    
    enum FormType
    {
        NoForm, 
        AcroForm, 
        XfaForm 
    };
 
    void setColorDisplayProfile(void *outputProfileA);
    void setColorDisplayProfileName(const QString &name);
    void *colorRgbProfile() const;
    void *colorDisplayProfile() const;
 
    static Document *load(const QString &filePath, const QByteArray &ownerPassword = QByteArray(), const QByteArray &userPassword = QByteArray());
 
    static Document *load(QIODevice *device, const QByteArray &ownerPassword = QByteArray(), const QByteArray &userPassword = QByteArray());
 
    static Document *loadFromData(const QByteArray &fileContents, const QByteArray &ownerPassword = QByteArray(), const QByteArray &userPassword = QByteArray());
 
    Page *page(int index) const;
 
    Page *page(const QString &label) const;
 
    int numPages() const;
 
    PageMode pageMode() const;
 
    PageLayout pageLayout() const;
 
    Qt::LayoutDirection textDirection() const;
 
    bool unlock(const QByteArray &ownerPassword, const QByteArray &userPassword);
 
    bool isLocked() const;
 
    QDateTime date(const QString &type) const;
 
    bool setDate(const QString &key, const QDateTime &val);
 
    QDateTime creationDate() const;
 
    bool setCreationDate(const QDateTime &val);
 
    QDateTime modificationDate() const;
 
    bool setModificationDate(const QDateTime &val);
 
    QString info(const QString &type) const;
 
    bool setInfo(const QString &key, const QString &val);
 
    QString title() const;
 
    bool setTitle(const QString &val);
 
    QString author() const;
 
    bool setAuthor(const QString &val);
 
    QString subject() const;
 
    bool setSubject(const QString &val);
 
    QString keywords() const;
 
    bool setKeywords(const QString &val);
 
    QString creator() const;
 
    bool setCreator(const QString &val);
 
    QString producer() const;
 
    bool setProducer(const QString &val);
 
    bool removeInfo();
 
    QStringList infoKeys() const;
 
    bool isEncrypted() const;
 
    bool isLinearized() const;
 
    bool okToPrint() const;
 
    bool okToPrintHighRes() const;
 
    bool okToChange() const;
 
    bool okToCopy() const;
 
    bool okToAddNotes() const;
 
    bool okToFillForm() const;
 
    bool okToCreateFormFields() const;
 
    bool okToExtractForAccessibility() const;
 
    bool okToAssemble() const;
 
    Q_DECL_DEPRECATED void getPdfVersion(int *major, int *minor) const;
 
    struct PdfVersion
    {
        int major;
        int minor;
    };
 
    PdfVersion getPdfVersion() const;
 
    QList<FontInfo> fonts() const;
 
    FontIterator *newFontIterator(int startPage = 0) const;
 
    QByteArray fontData(const FontInfo &fi) const;
 
    QList<EmbeddedFile *> embeddedFiles() const;
 
    bool hasEmbeddedFiles() const;
 
    Q_DECL_DEPRECATED QDomDocument *toc() const;
 
    QVector<OutlineItem> outline() const;
 
    LinkDestination *linkDestination(const QString &name);
 
    void setPaperColor(const QColor &color);
    QColor paperColor() const;
 
    void setRenderBackend(RenderBackend backend);
    RenderBackend renderBackend() const;
 
    static QSet<RenderBackend> availableRenderBackends();
 
    void setRenderHint(RenderHint hint, bool on = true);
    RenderHints renderHints() const;
 
    PSConverter *psConverter() const;
 
    PDFConverter *pdfConverter() const;
 
    QString metadata() const;
 
    bool hasOptionalContent() const;
 
    OptContentModel *optionalContentModel();
 
    QStringList scripts() const;
 
    bool getPdfId(QByteArray *permanentId, QByteArray *updateId) const;
 
    FormType formType() const;
 
    QVector<int> formCalculateOrder() const;
 
    QVector<FormFieldSignature *> signatures() const;
 
    bool xrefWasReconstructed() const;
 
    void setXRefReconstructedCallback(const std::function<void()> &callback);
 
    ~Document();
 
private:
    Q_DISABLE_COPY(Document)
 
    DocumentData *m_doc;
 
    explicit Document(DocumentData *dataA);
};
 
class BaseConverterPrivate;
class PSConverterPrivate;
class PDFConverterPrivate;
class POPPLER_QT5_EXPORT BaseConverter
{
    friend class Document;
 
public:
    virtual ~BaseConverter();
 
    void setOutputFileName(const QString &outputFileName);
 
    void setOutputDevice(QIODevice *device);
 
    virtual bool convert() = 0;
 
    enum Error
    {
        NoError,
        FileLockedError,
        OpenOutputError,
        NotSupportedInputFileError
    };
 
    Error lastError() const;
 
protected:
    explicit BaseConverter(BaseConverterPrivate &dd);
    Q_DECLARE_PRIVATE(BaseConverter)
    BaseConverterPrivate *d_ptr;
 
private:
    Q_DISABLE_COPY(BaseConverter)
};
 
class POPPLER_QT5_EXPORT PSConverter : public BaseConverter
{
    friend class Document;
 
public:
    enum PSOption
    {
        Printing = 0x00000001, 
        StrictMargins = 0x00000002,
        ForceRasterization = 0x00000004,
        PrintToEPS = 0x00000008, 
        HideAnnotations = 0x00000010 
    };
    Q_DECLARE_FLAGS(PSOptions, PSOption)
 
    
    ~PSConverter() override;
 
    void setPageList(const QList<int> &pageList);
 
    void setTitle(const QString &title);
 
    void setHDPI(double hDPI);
 
    void setVDPI(double vDPI);
 
    void setRotate(int rotate);
 
    void setPaperWidth(int paperWidth);
 
    void setPaperHeight(int paperHeight);
 
    void setRightMargin(int marginRight);
 
    void setBottomMargin(int marginBottom);
 
    void setLeftMargin(int marginLeft);
 
    void setTopMargin(int marginTop);
 
    void setStrictMargins(bool strictMargins);
 
    void setForceRasterize(bool forceRasterize);
 
    void setPSOptions(PSOptions options);
 
    PSOptions psOptions() const;
 
    void setPageConvertedCallback(void (*callback)(int page, void *payload), void *payload);
 
    bool convert() override;
 
private:
    Q_DECLARE_PRIVATE(PSConverter)
    Q_DISABLE_COPY(PSConverter)
 
    explicit PSConverter(DocumentData *document);
};
 
class POPPLER_QT5_EXPORT PDFConverter : public BaseConverter
{
    friend class Document;
 
public:
    enum PDFOption
    {
        WithChanges = 0x00000001 
    };
    Q_DECLARE_FLAGS(PDFOptions, PDFOption)
 
    
    ~PDFConverter() override;
 
    void setPDFOptions(PDFOptions options);
    PDFOptions pdfOptions() const;
 
    class POPPLER_QT5_EXPORT NewSignatureData
    {
    public:
        NewSignatureData();
        ~NewSignatureData();
        NewSignatureData(const NewSignatureData &) = delete;
        NewSignatureData &operator=(const NewSignatureData &) = delete;
 
        QString certNickname() const;
        void setCertNickname(const QString &certNickname);
 
        QString password() const;
        void setPassword(const QString &password);
 
        int page() const;
        void setPage(int page);
 
        QRectF boundingRectangle() const;
        void setBoundingRectangle(const QRectF &rect);
 
        QString signatureText() const;
        void setSignatureText(const QString &text);
 
        QString signatureLeftText() const;
        void setSignatureLeftText(const QString &text);
 
        QString reason() const;
        void setReason(const QString &reason);
 
        QString location() const;
        void setLocation(const QString &location);
 
        double fontSize() const;
        void setFontSize(double fontSize);
 
        double leftFontSize() const;
        void setLeftFontSize(double fontSize);
 
        QColor fontColor() const;
        void setFontColor(const QColor &color);
 
        QColor borderColor() const;
        void setBorderColor(const QColor &color);
 
        double borderWidth() const;
        void setBorderWidth(double width);
 
        QColor backgroundColor() const;
        void setBackgroundColor(const QColor &color);
 
        QString fieldPartialName() const;
        void setFieldPartialName(const QString &name);
 
        QByteArray documentOwnerPassword() const;
        void setDocumentOwnerPassword(const QByteArray &password);
 
        QByteArray documentUserPassword() const;
        void setDocumentUserPassword(const QByteArray &password);
 
        QString imagePath() const;
        void setImagePath(const QString &path);
 
    private:
        struct NewSignatureDataPrivate;
        NewSignatureDataPrivate *const d;
    };
 
    bool sign(const NewSignatureData &data);
 
    bool convert() override;
 
private:
    Q_DECLARE_PRIVATE(PDFConverter)
    Q_DISABLE_COPY(PDFConverter)
 
    explicit PDFConverter(DocumentData *document);
};
 
POPPLER_QT5_EXPORT Q_DECL_DEPRECATED QDateTime convertDate(char *dateString);
 
POPPLER_QT5_EXPORT QDateTime convertDate(const char *dateString);
 
POPPLER_QT5_EXPORT bool isCmsAvailable();
 
POPPLER_QT5_EXPORT bool isOverprintPreviewAvailable();
 
class SoundData;
class POPPLER_QT5_EXPORT SoundObject
{
public:
    enum SoundType
    {
        External, 
        Embedded 
    };
 
    enum SoundEncoding
    {
        Raw, 
        Signed, 
        muLaw, 
        ALaw 
    };
 
    explicit SoundObject(Sound *popplersound);
 
    ~SoundObject();
 
    SoundType soundType() const;
 
    QString url() const;
 
    QByteArray data() const;
 
    double samplingRate() const;
 
    int channels() const;
 
    int bitsPerSample() const;
 
    SoundEncoding soundEncoding() const;
 
private:
    Q_DISABLE_COPY(SoundObject)
 
    SoundData *m_soundData;
};
 
class MovieData;
class POPPLER_QT5_EXPORT MovieObject
{
    friend class AnnotationPrivate;
 
public:
    enum PlayMode
    {
        PlayOnce, 
        PlayOpen, 
        PlayRepeat, 
        PlayPalindrome 
    };
 
    ~MovieObject();
 
    QString url() const;
 
    QSize size() const;
 
    int rotation() const;
 
    bool showControls() const;
 
    PlayMode playMode() const;
 
    bool showPosterImage() const;
 
    QImage posterImage() const;
 
private:
    explicit MovieObject(AnnotMovie *ann);
 
    Q_DISABLE_COPY(MovieObject)
 
    MovieData *m_movieData;
};
 
}
 
Q_DECLARE_OPERATORS_FOR_FLAGS(Poppler::Page::PainterFlags)
Q_DECLARE_OPERATORS_FOR_FLAGS(Poppler::Page::SearchFlags)
Q_DECLARE_OPERATORS_FOR_FLAGS(Poppler::Document::RenderHints)
Q_DECLARE_OPERATORS_FOR_FLAGS(Poppler::PDFConverter::PDFOptions)
Q_DECLARE_OPERATORS_FOR_FLAGS(Poppler::PSConverter::PSOptions)
 
#endif
