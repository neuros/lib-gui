#ifndef _NMESSAGEDIALOG_H_
#define _NMESSAGEDIALOG_H_
/*
 *  Copyright(C) 2007 Neuros Technology International LLC.
 *               <www.neurostechnology.com>
 *
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, version 2 of the License.
 *
 *
 *  This program is distributed in the hope that, in addition to its
 *  original purpose to support Neuros hardware, it will be useful
 *  otherwise, but WITHOUT ANY WARRANTY; without even the implied
 *  warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *  See the GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 ****************************************************************************
 *
 * NMessageDialog implement header.
 *
 * REVISION:
 *
 * 1) Initial creation. ----------------------------------- 2007-12-11 WX
 *
 */

#include <QMessageBox>
#include "ui_nmessagedialog.h"

class NMessageDialogPrivate;

class NMessageDialog : public QDialog, private Ui::NMessageDialog
{
    Q_OBJECT
    Q_ENUMS(Interval)
    Q_PROPERTY(Qt::WindowModality windowModality READ windowModality WRITE setWindowModality)
    Q_PROPERTY(QString windowTitle READ windowTitle WRITE setWindowTitle)
    Q_PROPERTY(QString text READ text WRITE setText)
    Q_PROPERTY(QMessageBox::Icon icon READ icon WRITE setIcon)
    Q_PROPERTY(QPixmap iconPixmap READ iconPixmap WRITE setIconPixmap)
    Q_PROPERTY(Qt::TextFormat textFormat READ textFormat WRITE setTextFormat)
    Q_PROPERTY(Qt::Alignment textAlignment READ textAlignment WRITE setTextAlignment)
    Q_PROPERTY(Qt::Alignment titleAlignment READ titleAlignment WRITE setTitleAlignment)
    Q_PROPERTY(int interval READ interval WRITE setInterval)
    Q_PROPERTY(QMessageBox::StandardButtons standardButtons READ standardButtons WRITE setStandardButtons)

public:
    enum Interval
    {
        NeverTimeOut = -1
    };

    static QMessageBox::StandardButton information(QWidget *parent,
                                                   const QString &title,
                                                   const QString &text,
                                                   QMessageBox::StandardButtons buttons = QMessageBox::Ok,
                                                   QMessageBox::StandardButton defaultButton = QMessageBox::NoButton,
                                                   int timeout = NMessageDialog::NeverTimeOut);

    static QMessageBox::StandardButton question(QWidget *parent,
                                                const QString &title,
                                                const QString &text,
                                                QMessageBox::StandardButtons buttons = QMessageBox::Ok,
                                                QMessageBox::StandardButton defaultButton = QMessageBox::NoButton,
                                                int timeout = NMessageDialog::NeverTimeOut);

    static QMessageBox::StandardButton warning(QWidget *parent,
                                               const QString &title,
                                               const QString &text,
                                               QMessageBox::StandardButtons buttons = QMessageBox::Ok,
                                               QMessageBox::StandardButton defaultButton = QMessageBox::NoButton,
                                               int timeout = NMessageDialog::NeverTimeOut);

    static QMessageBox::StandardButton critical(QWidget *parent,
                                                const QString &title,
                                                const QString &text,
                                                QMessageBox::StandardButtons buttons = QMessageBox::Ok,
                                                QMessageBox::StandardButton defaultButton = QMessageBox::NoButton,
                                                int timeout = NeverTimeOut);

    explicit  NMessageDialog(QWidget * parent = NULL);
    NMessageDialog(QMessageBox::Icon icon,
                const QString & title,
                const QString & text,
                QMessageBox::StandardButtons buttons = QMessageBox::NoButton,
                QWidget * parent = NULL,
                Qt::WindowFlags f = Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    virtual ~NMessageDialog( );

    void addButton(QAbstractButton *button, QMessageBox::ButtonRole role);
    QPushButton *addButton(const QString &text, QMessageBox::ButtonRole role);
    QPushButton *addButton(QMessageBox::StandardButton button);
    void removeButton(QAbstractButton *button);

    void setStandardButtons(QMessageBox::StandardButtons buttons);
    QMessageBox::StandardButtons standardButtons( ) const;
    QMessageBox::StandardButton standardButton(QAbstractButton *button) const;
    QAbstractButton *button(QMessageBox::StandardButton which) const;

    QPushButton *defaultButton( ) const;
    void setDefaultButton(QPushButton *button);
    void setDefaultButton(QMessageBox::StandardButton button);

    QAbstractButton *escapeButton( ) const;
    void setEscapeButton(QAbstractButton *button);
    void setEscapeButton(QMessageBox::StandardButton button);

    QString buttonText(int button) const;
    void setButtonText(int button, const QString &text);

    QAbstractButton *clickedButton( ) const;

    Qt::WindowModality windowModality( ) const;
    void setWindowModality(Qt::WindowModality windowModality);

    QString windowTitle( ) const;
    void setWindowTitle(const QString &title);

    QString text( ) const;
    void setText(const QString &text);

    QMessageBox::Icon icon( ) const;
    void setIcon(QMessageBox::Icon icon);

    QPixmap iconPixmap( ) const;
    void setIconPixmap(const QPixmap &pixmap);

    Qt::TextFormat textFormat( ) const;
    void setTextFormat(Qt::TextFormat format);

    Qt::Alignment textAlignment( ) const;
    void setTextAlignment(Qt::Alignment alignment);

    Qt::Alignment titleAlignment( ) const;
    void setTitleAlignment(Qt::Alignment alignment);

    int interval( ) const;
    void setInterval(int msec);

    static QPixmap standardIcon(QMessageBox::Icon icon);

Q_SIGNALS:
    void timeout( );

public Q_SLOTS:
    virtual void done(int r);

private Q_SLOTS:
    void OnButtonClicked(QAbstractButton *button);
    void OnTimeOut( );

protected:
    void showEvent(QShowEvent *event);
    void resizeEvent(QResizeEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void closeEvent(QCloseEvent *event);

private:
    int execReturnCode(QAbstractButton *button);
    QAbstractButton *abstractButtonForId(int id) const;
    void detectEscapeButton( );

    void init( );
    void adjustButtons( );

private:
    NMessageDialogPrivate *d;

};

#endif // _NMESSAGEDIALOG_H_
