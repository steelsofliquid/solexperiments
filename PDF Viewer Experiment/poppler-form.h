/* poppler-form.h: qt interface to poppler
 * Copyright (C) 2007-2008, Pino Toscano <pino@kde.org>
 * Copyright (C) 2008, 2011, 2016, 2017, 2019-2022, Albert Astals Cid <aacid@kde.org>
 * Copyright (C) 2012, Adam Reichold <adamreichold@myopera.com>
 * Copyright (C) 2016, Hanno Meyer-Thurow <h.mth@web.de>
 * Copyright (C) 2017, Hans-Ulrich Jüttner <huj@froreich-bioscientia.de>
 * Copyright (C) 2017, Tobias C. Berner <tcberner@freebsd.org>
 * Copyright (C) 2018, Andre Heinecke <aheinecke@intevation.de>
 * Copyright (C) 2018, Chinmoy Ranjan Pradhan <chinmoyrp65@protonmail.com>
 * Copyright (C) 2018, Oliver Sander <oliver.sander@tu-dresden.de>
 * Copyright (C) 2019 João Netto <joaonetto901@gmail.com>
 * Copyright (C) 2019, Adrian Johnson <ajohnson@redneon.com>
 * Copyright (C) 2020, Thorsten Behrens <Thorsten.Behrens@CIB.de>
 * Copyright (C) 2020, Klarälvdalens Datakonsult AB, a KDAB Group company, <info@kdab.com>. Work sponsored by Technische Universität Dresden
 * Copyright (C) 2021, Theofilos Intzoglou <int.teo@gmail.com>
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
 
#ifndef _POPPLER_QT5_FORM_H_
#define _POPPLER_QT5_FORM_H_
 
#include <functional>
#include <memory>
#include <ctime>
#include <QtCore/QDateTime>
#include <QtCore/QVector>
#include <QtCore/QList>
#include <QtCore/QRectF>
#include <QtCore/QStringList>
#include <QtCore/QSharedPointer>
#include "poppler-export.h"
#include "poppler-annotation.h"
#include "poppler-qt5.h"
 
class Object;
class Page;
class FormWidget;
class FormWidgetButton;
class FormWidgetText;
class FormWidgetChoice;
class FormWidgetSignature;
 
namespace Poppler {
 
class DocumentData;
class Link;
 
class FormFieldData;
class FormFieldIconData;
 
class POPPLER_QT5_EXPORT FormFieldIcon
{
 
    friend class FormFieldIconData;
 
public:
    explicit FormFieldIcon(FormFieldIconData *data);
    FormFieldIcon(const FormFieldIcon &ffIcon);
    ~FormFieldIcon();
 
    FormFieldIcon &operator=(const FormFieldIcon &ffIcon);
 
private:
    FormFieldIconData *d_ptr;
};
class POPPLER_QT5_EXPORT FormField
{
 
    friend class FormFieldData;
 
public:
    enum FormType
    {
        FormButton, 
        FormText, 
        FormChoice, 
        FormSignature 
    };
 
    virtual ~FormField();
 
    virtual FormType type() const = 0;
 
    QRectF rect() const;
 
    int id() const;
 
    QString name() const;
 
    void setName(const QString &name) const;
 
    QString fullyQualifiedName() const;
 
    QString uiName() const;
 
    bool isReadOnly() const;
 
    void setReadOnly(bool value);
 
    bool isVisible() const;
 
    void setVisible(bool value);
 
    bool isPrintable() const;
 
    void setPrintable(bool value);
 
    Link *activationAction() const;
 
    enum AdditionalActionType
    {
        FieldModified, 
        FormatField, 
        ValidateField, 
        CalculateField, 
    };
    Link *additionalAction(AdditionalActionType type) const;
 
    Link *additionalAction(Annotation::AdditionalActionType type) const;
 
protected:
    explicit FormField(std::unique_ptr<FormFieldData> dd);
 
    std::unique_ptr<FormFieldData> m_formData;
 
private:
    Q_DISABLE_COPY(FormField)
};
 
class POPPLER_QT5_EXPORT FormFieldButton : public FormField
{
public:
    enum ButtonType
    {
        Push, 
        CheckBox, 
        Radio 
    };
 
    FormFieldButton(DocumentData *doc, ::Page *p, ::FormWidgetButton *w);
    ~FormFieldButton() override;
 
    FormType type() const override;
 
    ButtonType buttonType() const;
 
    QString caption() const;
 
    FormFieldIcon icon() const;
 
    void setIcon(const FormFieldIcon &icon);
 
    bool state() const;
 
    void setState(bool state);
 
    QList<int> siblings() const;
 
private:
    Q_DISABLE_COPY(FormFieldButton)
};
 
class POPPLER_QT5_EXPORT FormFieldText : public FormField
{
public:
    enum TextType
    {
        Normal, 
        Multiline, 
        FileSelect 
    };
 
    FormFieldText(DocumentData *doc, ::Page *p, ::FormWidgetText *w);
    ~FormFieldText() override;
 
    FormType type() const override;
 
    TextType textType() const;
 
    QString text() const;
 
    void setText(const QString &text);
 
    void setAppearanceText(const QString &text);
 
    bool isPassword() const;
 
    bool isRichText() const;
 
    int maximumLength() const;
 
    Qt::Alignment textAlignment() const;
 
    bool canBeSpellChecked() const;
 
    double getFontSize() const;
 
    void setFontSize(int fontSize);
 
private:
    Q_DISABLE_COPY(FormFieldText)
};
 
class POPPLER_QT5_EXPORT FormFieldChoice : public FormField
{
public:
    enum ChoiceType
    {
        ComboBox, 
        ListBox 
    };
 
    FormFieldChoice(DocumentData *doc, ::Page *p, ::FormWidgetChoice *w);
    ~FormFieldChoice() override;
 
    FormType type() const override;
 
    ChoiceType choiceType() const;
 
    QStringList choices() const;
 
    QVector<QPair<QString, QString>> choicesWithExportValues() const;
 
    bool isEditable() const;
 
    bool multiSelect() const;
 
    QList<int> currentChoices() const;
 
    void setCurrentChoices(const QList<int> &choice);
 
    QString editChoice() const;
 
    void setEditChoice(const QString &text);
 
    Qt::Alignment textAlignment() const;
 
    bool canBeSpellChecked() const;
 
private:
    Q_DISABLE_COPY(FormFieldChoice)
};
 
class CertificateInfoPrivate;
class POPPLER_QT5_EXPORT CertificateInfo
{
public:
    enum PublicKeyType
    {
        RsaKey,
        DsaKey,
        EcKey,
        OtherKey
    };
 
    enum KeyUsageExtension
    {
        KuDigitalSignature = 0x80,
        KuNonRepudiation = 0x40,
        KuKeyEncipherment = 0x20,
        KuDataEncipherment = 0x10,
        KuKeyAgreement = 0x08,
        KuKeyCertSign = 0x04,
        KuClrSign = 0x02,
        KuEncipherOnly = 0x01,
        KuNone = 0x00
    };
    Q_DECLARE_FLAGS(KeyUsageExtensions, KeyUsageExtension)
 
    
    enum EntityInfoKey
    {
        CommonName,
        DistinguishedName,
        EmailAddress,
        Organization,
    };
 
    CertificateInfo();
    explicit CertificateInfo(CertificateInfoPrivate *priv);
    ~CertificateInfo();
 
    bool isNull() const;
 
    int version() const;
 
    QByteArray serialNumber() const;
 
    QString issuerInfo(EntityInfoKey key) const;
 
    QString subjectInfo(EntityInfoKey key) const;
 
    QString nickName() const;
 
    QDateTime validityStart() const;
 
    QDateTime validityEnd() const;
 
    KeyUsageExtensions keyUsageExtensions() const;
 
    QByteArray publicKey() const;
 
    PublicKeyType publicKeyType() const;
 
    int publicKeyStrength() const;
 
    bool isSelfSigned() const;
 
    QByteArray certificateData() const;
 
    bool checkPassword(const QString &password) const;
 
    CertificateInfo(const CertificateInfo &other);
    CertificateInfo &operator=(const CertificateInfo &other);
 
private:
    Q_DECLARE_PRIVATE(CertificateInfo)
 
    QSharedPointer<CertificateInfoPrivate> d_ptr;
};
Q_DECLARE_OPERATORS_FOR_FLAGS(CertificateInfo::KeyUsageExtensions)
 
 
class SignatureValidationInfoPrivate;
class POPPLER_QT5_EXPORT SignatureValidationInfo
{
public:
    enum SignatureStatus
    {
        SignatureValid, 
        SignatureInvalid, 
        SignatureDigestMismatch, 
        SignatureDecodingError, 
        SignatureGenericError, 
        SignatureNotFound, 
        SignatureNotVerified 
    };
 
    enum CertificateStatus
    {
        CertificateTrusted, 
        CertificateUntrustedIssuer, 
        CertificateUnknownIssuer, 
        CertificateRevoked, 
        CertificateExpired, 
        CertificateGenericError, 
        CertificateNotVerified 
    };
 
    enum HashAlgorithm
    {
        HashAlgorithmUnknown,
        HashAlgorithmMd2,
        HashAlgorithmMd5,
        HashAlgorithmSha1,
        HashAlgorithmSha256,
        HashAlgorithmSha384,
        HashAlgorithmSha512,
        HashAlgorithmSha224
    };
 
    explicit SignatureValidationInfo(SignatureValidationInfoPrivate *priv);
    ~SignatureValidationInfo();
 
    SignatureStatus signatureStatus() const;
 
    CertificateStatus certificateStatus() const;
 
    QString signerName() const;
 
    QString signerSubjectDN() const;
 
    QString location() const;
 
    QString reason() const;
 
    HashAlgorithm hashAlgorithm() const;
 
    time_t signingTime() const;
 
    QByteArray signature() const;
 
    QList<qint64> signedRangeBounds() const;
 
    bool signsTotalDocument() const;
 
    CertificateInfo certificateInfo() const;
 
    SignatureValidationInfo(const SignatureValidationInfo &other);
    SignatureValidationInfo &operator=(const SignatureValidationInfo &other);
 
private:
    Q_DECLARE_PRIVATE(SignatureValidationInfo)
 
    QSharedPointer<SignatureValidationInfoPrivate> d_ptr;
};
 
class POPPLER_QT5_EXPORT FormFieldSignature : public FormField
{
public:
    enum SignatureType
    {
        AdbePkcs7sha1,
        AdbePkcs7detached,
        EtsiCAdESdetached,
        UnknownSignatureType, 
        UnsignedSignature 
    };
 
    enum ValidateOptions
    {
        ValidateVerifyCertificate = 1, 
        ValidateForceRevalidation = 2, 
        ValidateWithoutOCSPRevocationCheck = 4, 
        ValidateUseAIACertFetch = 8 
    };
 
    FormFieldSignature(DocumentData *doc, ::Page *p, ::FormWidgetSignature *w);
    ~FormFieldSignature() override;
 
    FormType type() const override;
 
    SignatureType signatureType() const;
 
    SignatureValidationInfo validate(ValidateOptions opt) const;
 
    SignatureValidationInfo validate(int opt, const QDateTime &validationTime) const;
 
    enum SigningResult
    {
        FieldAlreadySigned, 
        GenericSigningError,
        SigningSuccess
    };
 
    SigningResult sign(const QString &outputFileName, const PDFConverter::NewSignatureData &data) const;
 
private:
    Q_DISABLE_COPY(FormFieldSignature)
};
 
bool POPPLER_QT5_EXPORT hasNSSSupport();
 
QVector<CertificateInfo> POPPLER_QT5_EXPORT getAvailableSigningCertificates();
 
QString POPPLER_QT5_EXPORT getNSSDir();
 
void POPPLER_QT5_EXPORT setNSSDir(const QString &pathURL);
 
void POPPLER_QT5_EXPORT setNSSPasswordCallback(const std::function<char *(const char *)> &f);
}
 
#endif
