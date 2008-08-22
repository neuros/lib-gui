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
 * NMessageDialog implement routines.
 *
 * REVISION:
 *
 * 1) Initial creation. ----------------------------------- 2007-12-11 WX
 * 2) Add multi language support. ------------------------- 2008-02-28 JChen
 *
 */

//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include <QDesktopWidget>
#include <QCoreApplication>
#include <QCloseEvent>
#include <QScrollBar>
#include <QPushButton>
#include <QPixmapCache>
#include <QTimer>
#include <QPainter>

#include "nmessagedialog.h"
#include "nmessagedialog_p.h"

#define IMAGE_BACKGROUND ":/lib-gui/msgdialog-tile.png"
#define ICON_INFORMATION ":/lib-gui/info.gif"
#define ICON_WARNING ":/lib-gui/warning.gif"
#define ICON_CRITICAL ":/lib-gui/error.gif"
#define ICON_QUESTION ":/lib-gui/query.gif"

/*
 * Constructs a message box with no text and no buttons.
 * If parent is NULL, the message box becomes an application-global modal dialog box.
 * If parent is a widget, the message box becomes modal relative to parent.
 * The parent argument is passed to the QDialog constructor.
 */
NMessageDialog::NMessageDialog (QWidget * parent)
:QDialog(parent), d(new NMessageDialogPrivate)
{
    setupUi(this);
    init( );
}

/*
 * Constructs a message box with the given icon, title, text, and standard buttons.
 * (Buttons can also be added at any time using addButton().)
 * If parent is 0, the message box becomes an application-global modal dialog box.
 * If parent is a widget, the message box becomes modal relative to parent.
 * The parent and f arguments are passed to the QDialog constructor.
 */
NMessageDialog::NMessageDialog (QMessageBox::Icon icon, const QString & title,
                          const QString & text, QMessageBox::StandardButtons buttons,
                          QWidget * parent,Qt::WindowFlags f)
:QDialog(parent, f), d(new NMessageDialogPrivate)
{
    setupUi(this);
    init( );

    setIcon(icon);
    setWindowTitle(title);
    setText(text);

    if (buttons != QMessageBox::NoButton)
        setStandardButtons(buttons);
}

/*
 * Destroys the message box.
 */
NMessageDialog::~NMessageDialog( )
{
    if (d != NULL)
    {
        delete d;
        d = NULL;
    }
}

/*
 * Internal Initialise the messagebox, setup the background, etc
 */
void NMessageDialog::init( )
{
    d->titleLabel = this->titleLabel;
    d->textLabel = this->textLabel;
    d->iconLabel = this->iconLabel;
    d->textScrollArea = this->textScrollArea;
    d->buttonBox = this->buttonBox;

    d->autoAddOkButton = true;
    d->icon = QMessageBox::NoIcon;
    d->timer->setInterval(NMessageDialog::NeverTimeOut);
    d->escapeButton = NULL;
    d->defaultButton = NULL;
    d->clickedButton = NULL;
    d->detectedEscapeButton = NULL;

    /* Set the QScrollArea transparent to his parent window */
    d->textScrollArea->viewport( )->setAutoFillBackground(false);
    d->textScrollArea->widget( )->setAutoFillBackground(false);

    /* connect signals and slots */
    QObject::connect(d->buttonBox, SIGNAL(clicked(QAbstractButton*)),
                     this, SLOT(OnButtonClicked(QAbstractButton*)));
    QObject::connect(d->timer, SIGNAL(timeout( )),
                     this, SLOT(OnTimeOut( )));

    /* initialise the default size and position */
    QRect screenRect;
    QWidget* parent = parentWidget( );
    if (parent != NULL)
        screenRect = parent->geometry( );
    else
        screenRect = QApplication::desktop( )->geometry( );

    resize(screenRect.width( ), screenRect.height( )/2);
    move(screenRect.x( ), screenRect.y() + (screenRect.height( ) - height( ))/2);
}

/*
 * Adds the given button to the message box with the specified role.
 */
void NMessageDialog::addButton(QAbstractButton *button, QMessageBox::ButtonRole role)
{
    if (button == NULL)
        return;
    removeButton(button);
    d->buttonBox->addButton(button, (QDialogButtonBox::ButtonRole)role);
    d->autoAddOkButton = false;
}

/*
 * Creates a button with the given text, adds it to the message box for the specified role, and returns it.
 */
QPushButton * NMessageDialog::addButton(const QString &text, QMessageBox::ButtonRole role)
{
    QPushButton *pushButton = new QPushButton(text);
    addButton(pushButton, role);
    return pushButton;
}

/*
 * Adds a standard button to the message box if it is valid to do so, and returns the push button.
 */
QPushButton * NMessageDialog::addButton(QMessageBox::StandardButton button)
{
    QPushButton *pushButton = d->buttonBox->addButton((QDialogButtonBox::StandardButton)button);
    if (pushButton != NULL)
        d->autoAddOkButton = false;
    return pushButton;
}

/*
 * Removes button from the button box without deleting it.
 */
void NMessageDialog::removeButton(QAbstractButton *button)
{
    if (d->escapeButton == button)
        d->escapeButton = NULL;
    if (d->defaultButton == button)
        d->defaultButton = NULL;
    d->buttonBox->removeButton(button);
}

/*
 * return which standard buttons are used by the message box.
 */
QMessageBox::StandardButtons NMessageDialog::standardButtons( ) const
{
    return QMessageBox::StandardButtons(int(d->buttonBox->standardButtons( )));
}

/*
 * set the standard buttons of the messagebox to buttons
 */
void NMessageDialog::setStandardButtons(QMessageBox::StandardButtons buttons)
{
    d->buttonBox->setStandardButtons(QDialogButtonBox::StandardButtons(int(buttons)));
    QList<QAbstractButton *> buttonList = d->buttonBox->buttons( );
    if (!buttonList.contains(d->escapeButton))
        d->escapeButton = NULL;
    if (!buttonList.contains(d->defaultButton))
        d->defaultButton = NULL;
    d->autoAddOkButton = false;
}

/*
 * Returns the standard button enum value corresponding to the given button,
 * or NoButton if the given button isn't a standard button.
 */
QMessageBox::StandardButton NMessageDialog::standardButton(QAbstractButton *button) const
{
    return(QMessageBox::StandardButton)d->buttonBox->standardButton(button);
}

/*
 * Returns a pointer corresponding to the standard button which,
 * or 0 if the standard button doesn't exist in this message box.
 */
QAbstractButton * NMessageDialog::button(QMessageBox::StandardButton which) const
{
    return d->buttonBox->button(QDialogButtonBox::StandardButton(which));
}

/*
 * Returns the button that should be the message box's default button.
 * Returns 0 if no default button was set.
 */
QPushButton * NMessageDialog::defaultButton( ) const
{
    return d->defaultButton;
}

/*
 * Sets the message box's default button to button.
 */
void NMessageDialog::setDefaultButton(QPushButton *button)
{
    if (!d->buttonBox->buttons( ).contains(button))
        return;
    d->defaultButton = button;
    button->setDefault(true);
    button->setFocus( );
}

/*
 * Sets the message box's default button to button.
 */
void NMessageDialog::setDefaultButton(QMessageBox::StandardButton button)
{
    setDefaultButton(d->buttonBox->button(QDialogButtonBox::StandardButton(button)));
}

/*
 * Returns the button that is activated when escape is pressed.
 * By default, QMessageBox attempts to automatically detect an escape button as follows:
 * 1. If there is only one button, it is made the escape button.
 * 2. If there is a Cancel button, it is made the escape button.
 * 3. if there is exactly one button with the role QMessageBox::RejectRole, it is made the escape button.
 * When an escape button could not be automatically detected, pressing Esc has no effect.
 */
QAbstractButton * NMessageDialog::escapeButton( ) const
{
    return d->escapeButton;
}

/*
 * Sets the button that gets activated when the Escape key is pressed to button.
 */
void NMessageDialog::setEscapeButton(QAbstractButton *button)
{
    if (d->buttonBox->buttons( ).contains(button))
        d->escapeButton = button;
}

/*
 * Sets the buttons that gets activated when the Escape key is pressed to button.
 */
void NMessageDialog::setEscapeButton(QMessageBox::StandardButton button)
{
    setEscapeButton(d->buttonBox->button(QDialogButtonBox::StandardButton(button)));
}

/*
 * Returns the text of the message box button button,
 * or an empty string if the message box does not contain the button.
 */
QString NMessageDialog::buttonText(int button) const
{
    if (QAbstractButton *abstractButton = abstractButtonForId(button))
        return abstractButton->text( );
    return QString( );
}

/*
 * Sets the text of the message box button button to text.
 * Setting the text of a button that is not in the message box is silently ignored.
 */
void NMessageDialog::setButtonText(int button, const QString &text)
{
    if (QAbstractButton *abstractButton = abstractButtonForId(button))
        abstractButton->setText(text);
}

/*
 * Returns the button that was clicked by the user,
 * or 0 if the user hit the Esc key and no escape button was set.
 * If exec() hasn't been called yet, returns 0.
 */
QAbstractButton * NMessageDialog::clickedButton( ) const
{
    return d->clickedButton;
}

/*
 * This property holds which windows are blocked by the modal widget.
 * This property only makes sense for windows.
 * A modal widget prevents widgets in other windows from getting input.
 * The value of this property controls which windows are blocked when the widget is visible.
 * Changing this property while the window is visible has no effect;
 * you must hide() the widget first, then show() it again.
 * By default, this property is Qt::NonModal.
 */
Qt::WindowModality NMessageDialog::windowModality( ) const
{
    return QDialog::windowModality( );
}

/*
 * This function shadows QWidget::setWindowModality( ).
 * Sets the modality of the message box to windowModality.
 */
void NMessageDialog::setWindowModality(Qt::WindowModality windowModality)
{
    QDialog::setWindowModality(windowModality);

    if ((parentWidget( ) != NULL) && (windowModality == Qt::WindowModal))
        setParent(parentWidget( ), Qt::Sheet);
    else
        setParent(parentWidget( ), Qt::Dialog);
    setDefaultButton(d->defaultButton);
}

/*
 * return the window title of the message box
 */
QString NMessageDialog::windowTitle( ) const
{
    return d->titleLabel->text( );
}

/*
 * This function shadows QWidget::setWindowTitle( ).
 * Sets the title of the message box to title.
 */
void NMessageDialog::setWindowTitle(const QString &title)
{
    d->titleLabel->setText(title);
}

/*
 * This property holds the message box text to be displayed.
 * The text will be interpreted either as a plain text or as rich text, depending on the text format setting (QMessageBox::textFormat). The default setting is Qt::AutoText, i.e. the message box will try to auto-detect the format of the text.
 * The default value of this property is an empty string.
 */
QString NMessageDialog::text( ) const
{
    return d->textLabel->text( );
}

void NMessageDialog::setText(const QString &text)
{
    d->textLabel->setText(text);
}

/*
 * This property holds the message box's icon.
 * You can also set a custom pixmap icon using the QMessageBox::iconPixmap property.
 * The default icon is QMessageBox::NoIcon.
 */
QMessageBox::Icon NMessageDialog::icon( ) const
{
    return d->icon;
}

void NMessageDialog::setIcon(QMessageBox::Icon icon)
{
    if (icon == d->icon)
        return;
    d->icon = icon;
    d->iconLabel->clear( );
    d->iconLabel->setPixmap(standardIcon(d->icon).scaled(iconLabel->size( )));
}

/*
 * This property holds the icon currently used by the message box.
 */
QPixmap NMessageDialog::iconPixmap( ) const
{
    return *d->iconLabel->pixmap( );
}

void NMessageDialog::setIconPixmap(const QPixmap &pixmap)
{
    d->iconLabel->clear( );
    d->iconLabel->setPixmap(pixmap.scaled(iconLabel->size( )));
    d->icon = QMessageBox::NoIcon;
}

/*
 * This property holds the format of the text displayed by the message box.
 * The default format is Qt::AutoText.
 */
Qt::TextFormat NMessageDialog::textFormat( ) const
{
    return d->textLabel->textFormat( );
}

void NMessageDialog::setTextFormat(Qt::TextFormat format)
{
    d->textLabel->setTextFormat(format);
}

Qt::Alignment NMessageDialog::textAlignment( ) const
{
    return d->textLabel->alignment( );
}

void NMessageDialog::setTextAlignment(Qt::Alignment alignment)
{
    d->textLabel->setAlignment(alignment);
}

Qt::Alignment NMessageDialog::titleAlignment( ) const
{
    d->titleLabel->alignment( );
}

void NMessageDialog::setTitleAlignment(Qt::Alignment alignment)
{
    d->titleLabel->setAlignment(alignment);
}

/*
 * return the timeout interval of the message box.
 */
int NMessageDialog::interval( ) const
{
    return d->timer->interval( );
}

/*
 * A timeout interval of 0 will time out as soon as all the events
 * in the window system's event queue have been processed.
 */
void NMessageDialog::setInterval(int msec)
{
    d->timer->setInterval(msec);
}

QPixmap NMessageDialog::standardIcon(QMessageBox::Icon icon)
{
    QString iconName;
    switch (icon)
    {
    case QMessageBox::NoIcon:
    default:
        break;
    case QMessageBox::Information:
        iconName = ICON_INFORMATION;
        break;
    case QMessageBox::Warning:
        iconName = ICON_WARNING;
        break;
    case QMessageBox::Critical:
        iconName = ICON_CRITICAL;
        break;
    case QMessageBox::Question:
        iconName = ICON_QUESTION;
        break;
    }

    QPixmap tmpIconPixmap;
    if (!iconName.isEmpty( ))
    {
        if (!QPixmapCache::find(iconName, tmpIconPixmap))
        {
            tmpIconPixmap = QPixmap(iconName);
            QPixmapCache::insert(iconName, tmpIconPixmap);
        }
    }

    return tmpIconPixmap;
}

static QMessageBox::StandardButton newButton(int button)
{
#define NewButtonFlag 0xFFFFFC00
    if (button == QMessageBox::NoButton || (button & NewButtonFlag))
        return QMessageBox::StandardButton(button & QMessageBox::ButtonMask);
    return QMessageBox::NoButton;
}

QAbstractButton *NMessageDialog::abstractButtonForId(int id) const
{
    QAbstractButton *result = d->buttonBox->buttons( ).value(id);
    if (result != NULL)
        return result;
    return button(newButton(id));
}

void NMessageDialog::detectEscapeButton()
{
    if (d->escapeButton != NULL)
        d->detectedEscapeButton = d->escapeButton;
    else if ((d->detectedEscapeButton = d->buttonBox->button(QDialogButtonBox::Cancel)) != NULL)
        return;
    else if (d->buttonBox->buttons( ).count( ) == 1)
        d->detectedEscapeButton = d->buttonBox->buttons( ).first( );
    else
    {
        if (d->detectedEscapeButton != NULL)
            return;

        const QList<QAbstractButton *> buttons = d->buttonBox->buttons( );
        for (int i = buttons.count( ); i >=0; i --)
        {
            if (d->buttonBox->buttonRole(buttons.at(i)) == QDialogButtonBox::RejectRole)
            {
                d->detectedEscapeButton = buttons.at(i);
                return;
            }
        }
    }
}

void NMessageDialog::resizeEvent(QResizeEvent *event)
{
    QDialog::resizeEvent(event);
    QPixmap pixmap(size( ));
    QPainter painter(&pixmap);
    painter.drawTiledPixmap(rect( ), d->tiledBackground->scaled(d->tiledBackground->width( ),
                                                                height( )), QPoint(0, 0));
    QPalette pal = palette( );
    QBrush b = QBrush(pixmap);
    pal.setBrush(backgroundRole( ), b);
    setPalette(pal);
}

void NMessageDialog::showEvent(QShowEvent *event)
{
    QDialog::showEvent(event);

    if (d->autoAddOkButton)
        addButton(QMessageBox::Ok);

    adjustButtons( );
    detectEscapeButton( );

    if (d->timer->interval( ) != NMessageDialog::NeverTimeOut)
        d->timer->start( );
}

void NMessageDialog::closeEvent(QCloseEvent *event)
{
    d->timer->stop( );
    if (d->detectedEscapeButton == NULL)
    {
        event->ignore( );
        QDialog::closeEvent(event);
        return;
    }

    QDialog::closeEvent(event);
    d->clickedButton = d->detectedEscapeButton;
    setResult(execReturnCode(d->detectedEscapeButton));
}

void NMessageDialog::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_PageUp:
    case Qt::Key_PageDown:
    case Qt::Key_Up:
    case Qt::Key_Down:
        {
            QScrollBar *vbar = d->textScrollArea->verticalScrollBar( );
            if (vbar != NULL)
            {
                switch (event->key( ))
                {
                case Qt::Key_PageUp:
                    vbar->triggerAction(QAbstractSlider::SliderPageStepSub);
                    break;
                case Qt::Key_PageDown:
                    vbar->triggerAction(QAbstractSlider::SliderPageStepAdd);
                    break;
                case Qt::Key_Up:
                    vbar->triggerAction(QAbstractSlider::SliderSingleStepSub);
                    break;
                case Qt::Key_Down:
                    vbar->triggerAction(QAbstractSlider::SliderSingleStepAdd);
                    break;
                }
            }
        }
        break;
    case Qt::Key_Escape:
        if (d->detectedEscapeButton != NULL)
            d->detectedEscapeButton->click( );
        break;
    case Qt::Key_HomePage:
        reject( );
        break;
    default:
        QDialog::keyPressEvent(event);
        break;
    }
}

int NMessageDialog::execReturnCode(QAbstractButton *button)
{
    int ret = d->buttonBox->standardButton(button);
    if (ret == QMessageBox::NoButton)
        ret = d->buttonBox->buttons( ).indexOf(button); // if button == 0, correctly sets ret = -1

    return ret;
}

void NMessageDialog::OnButtonClicked(QAbstractButton *button)
{
    d->clickedButton = button;
    done(execReturnCode(button)); // does not trigger closeEvent, but it will close messagebox
}

void NMessageDialog::OnTimeOut( )
{
    emit timeout( );
    done(-1);
}

void NMessageDialog::done(int r)
{
    d->timer->stop( );
    QDialog::done(r);
}

void NMessageDialog::adjustButtons( )
{
    int buttonsCount(d->buttonBox->buttons( ).count( ));
    if (buttonsCount <= 1) //It is unnecessary to adjust buttons spacing
        return;

    int buttonsWidth(0);
    Q_FOREACH(QAbstractButton *aBtn, d->buttonBox->buttons( ))
    buttonsWidth += aBtn->width( );

    int boxMargin(d->buttonBox->width( ) - buttonsWidth);

    if (d->defButtonsSpacing * (buttonsCount - 1) <= boxMargin) //try to set the buttons spacing as base spacing
        d->buttonBox->layout( )->setSpacing(d->defButtonsSpacing);
    else if (d->defButtonsMinSpacing * (buttonsCount - 1) <= boxMargin) //try to set the buttons spacing as min spacing
        d->buttonBox->layout( )->setSpacing(d->defButtonsMinSpacing);

    // otherwise, let Qt to layout buttons itself.
}



QMessageBox::StandardButton NMessageDialog::information(QWidget *parent,
                                                     const QString &title,
                                                     const QString &text,
                                                     QMessageBox::StandardButtons buttons,
                                                     QMessageBox::StandardButton defaultButton,
                                                     int timeout)
{
    NMessageDialog msgbox(QMessageBox::Information, title, text, buttons);
    msgbox.setDefaultButton(defaultButton);
    msgbox.setInterval(timeout);
    return QMessageBox::StandardButton(int(msgbox.exec()));
}



QMessageBox::StandardButton NMessageDialog::question(QWidget *parent,
                                                  const QString &title,
                                                  const QString &text,
                                                  QMessageBox::StandardButtons buttons,
                                                  QMessageBox::StandardButton defaultButton,
                                                  int timeout)
{
    NMessageDialog msgbox(QMessageBox::Question, title, text, buttons);
    msgbox.setDefaultButton(defaultButton);
    msgbox.setInterval(timeout);
    return QMessageBox::StandardButton(int(msgbox.exec()));
}

QMessageBox::StandardButton NMessageDialog::warning(QWidget *parent,
                                                 const QString &title,
                                                 const QString &text,
                                                 QMessageBox::StandardButtons buttons,
                                                 QMessageBox::StandardButton defaultButton,
                                                 int timeout)
{
    NMessageDialog msgbox(QMessageBox::Warning, title, text, buttons);
    msgbox.setDefaultButton(defaultButton);
    msgbox.setInterval(timeout);
    return QMessageBox::StandardButton(int(msgbox.exec()));
}

QMessageBox::StandardButton NMessageDialog::critical(QWidget *parent,
                                                  const QString &title,
                                                  const QString &text,
                                                  QMessageBox::StandardButtons buttons,
                                                  QMessageBox::StandardButton defaultButton,
                                                  int timeout)
{
    NMessageDialog msgbox(QMessageBox::Critical, title, text, buttons);
    msgbox.setDefaultButton(defaultButton);
    msgbox.setInterval(timeout);
    return QMessageBox::StandardButton(int(msgbox.exec()));
}



NMessageDialogPrivate::NMessageDialogPrivate( )
{
    timer = new QTimer;
    tiledBackground = new QPixmap(IMAGE_BACKGROUND);
}

NMessageDialogPrivate::~NMessageDialogPrivate( )
{
    delete timer;
    delete tiledBackground;
}
