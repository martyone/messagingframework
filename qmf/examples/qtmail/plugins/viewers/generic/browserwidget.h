/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt Messaging Framework.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef BROWSERWIDGET_H
#define BROWSERWIDGET_H

#include <qmailaddress.h>
#include <QList>
#include <QSet>
#include <QString>
#include <QUrl>
#include <QWidget>

class QMailMessage;
class QMailMessagePart;
class QMailMessagePartContainer;
#ifdef USE_WEBKIT
class ContentAccessManager;
class QWebView;
#else
class ContentRenderer;
#endif

class BrowserWidget : public QWidget
{
    Q_OBJECT

public:
    BrowserWidget(QWidget *parent = 0);

#ifndef USE_WEBKIT
    void setResource(const QUrl& name, QVariant var);
#endif

    void clearResources();

    void setMessage( const QMailMessage& mail, bool plainTextMode );

    QList<QString> embeddedNumbers() const;

    static QString encodeUrlAndMail(const QString& txt);

    void scrollToAnchor(const QString& anchor);
    void setPlainText(const QString& text);

    void addAction(QAction* action);
    void addActions(const QList<QAction*>& actions);
    void removeAction(QAction* action);

signals:
    void anchorClicked(const QUrl&);

public slots:
    virtual void setSource(const QUrl &name);

private slots:
    void contextMenuRequested(const QPoint& pos);

private:
    void displayPlainText(const QMailMessage* mail);
    void displayHtml(const QMailMessage* mail);

    void setTextResource(const QSet<QUrl>& names, const QString& textData, const QString &contentType);
    void setImageResource(const QSet<QUrl>& names, const QByteArray& imageData, const QString &contentType);
    void setPartResource(const QMailMessagePart& part);

    QString renderSimplePart(const QMailMessagePart& part);
    QString renderAttachment(const QMailMessagePart& part);
    QString renderPart(const QMailMessagePart& part);
    QString renderMultipart(const QMailMessagePartContainer& partContainer);

    QString describeMailSize(uint bytes) const;
    QString formatText(const QString& txt) const;
    QString smsBreakReplies(const QString& txt) const;
    QString noBreakReplies(const QString& txt) const;
    QString handleReplies(const QString& txt) const;
    QString buildParagraph(const QString& txt, const QString& prepend, bool preserveWs = false) const;
    static QString listRefMailTo(const QList<QMailAddress>& list);
    static QString refMailTo(const QMailAddress& address);
    static QString refNumber(const QString& number);
    static QString refUrl(const QString& url, const QString& scheme, const QString& leading, const QString& trailing);

private:
    QString (BrowserWidget::*replySplitter)(const QString&) const;
    mutable QList<QString> numbers;
#ifdef USE_WEBKIT
    ContentAccessManager *m_accessManager;
    QWebView* m_webView;
#else
    ContentRenderer *m_renderer;
#endif

private:
    friend class GenericComposer;
};

#endif
