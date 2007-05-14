/*
    Copyright (C) 2007 by Robert Knight <robertknight@gmail.com>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
    02110-1301  USA.
*/

#ifndef EDITSESSIONDIALOG_H
#define EDITSESSIONDIALOG_H

// Qt
#include <QtGui/QAbstractItemDelegate>
#include <QtCore/QPair>
#include <QtCore/QHash>
#include <QtCore/QSet>

// KDE
#include <KDialog>

class QAbstractButton;

namespace Ui
{
    class EditProfileDialog;
}

namespace Konsole
{

class Profile;

/**
 * A dialog which allows the user to edit a profile.
 * After the dialog is created, it can be initialised with the settings
 * for a profile using setProfile().  When the user makes changes to the 
 * dialog and accepts the changes, the dialog will update the
 * profile in the SessionManager by calling the SessionManager's 
 * changeProfile() method.
 *
 * Some changes made in the dialog are preview-only changes which cause
 * the SessionManager's changeProfile() method to be called with
 * the persistant argument set to false.  These changes are then
 * un-done when the dialog is closed.
 *
 * TODO: More documentation
 */
class EditProfileDialog : public KDialog
{
Q_OBJECT

public:
    /** Constructs a new dialog with the specified parent. */
    EditProfileDialog(QWidget* parent = 0);
    virtual ~EditProfileDialog();

    /**
     * Initialises the dialog with the settings for the specified session
     * type.
     *
     * When the dialog closes, the profile will be updated in the SessionManager
     * with the altered settings.
     *
     * @param key The key for the session type provided by the SessionManager instance
     */
    void setProfile(const QString& key);

public slots:
    // reimplemented
    virtual void accept();
    // reimplemented 
    virtual void reject();

protected:
    virtual bool eventFilter(QObject* watched , QEvent* event);

private slots:
    // saves changes to profile
    void save();

    // general page
    void selectInitialDir();
    void selectIcon();

    void profileNameChanged(const QString& text);
    void initialDirChanged(const QString& text);
    void commandChanged(const QString& text);
    void tabTitleFormatChanged(const QString& text);
    void remoteTabTitleFormatChanged(const QString& text);

    void insertTabTitleText(const QString& text);
    void insertRemoteTabTitleText(const QString& text);

    void showMenuBar(bool);
    void alwaysHideTabBar();
    void alwaysShowTabBar();
    void showTabBarAsNeeded();

    // appearance page
    void setFontSize(int pointSize);
    void showFontDialog();
    void newColorScheme();
    void editColorScheme();
    void removeColorScheme();
    void colorSchemeSelected();
    void previewColorScheme(const QModelIndex& index);
    void fontSelected(const QFont&);
    //void previewFont(const QFont&);

    // scrolling page
    void noScrollBack();
    void fixedScrollBack();
    void unlimitedScrollBack();
   
    void scrollBackLinesChanged(int);

    void hideScrollBar();
    void showScrollBarLeft();
    void showScrollBarRight();

    // keyboard page
    void editKeyBinding();
    void newKeyBinding();
    void keyBindingSelected();
    void removeKeyBinding();

    // advanced page
    void toggleBlinkingText(bool);
    void toggleFlowControl(bool);
    void toggleResizeWindow(bool);
    void toggleBlinkingCursor(bool);

    void setCursorShape(int);
    void autoCursorColor();
    void customCursorColor();
    void customCursorColorChanged(const QColor&);
    void wordCharactersChanged(const QString&);


private:
    // initialize various pages of the dialog
    void setupGeneralPage(const Profile* info);
    void setupAppearancePage(const Profile* info);
    void setupKeyboardPage(const Profile* info);
    void setupScrollingPage(const Profile* info);
    void setupAdvancedPage(const Profile* info);

    void updateColorSchemeList();
    void updateKeyBindingsList();

    void showColorSchemeEditor(bool newScheme);
    void showKeyBindingEditor(bool newTranslator);

    void changeCheckedItem( QAbstractItemModel* mode,  const QModelIndex& to );

    void preview(int property , QVariant value);
    void unpreview(int property);
    void unpreviewAll();

    struct RadioOption
    {
       QAbstractButton* button;
       int property;
       char* slot; 
    };
    void setupRadio(RadioOption* possible,int actual);
    struct ComboOption
    {
       QAbstractButton* button;
       int property;
       char* slot;
    };
    void setupCombo(ComboOption* options , const Profile* profile);

    Ui::EditProfileDialog* _ui;
    Profile* _tempProfile;
    QString _profileKey;

    QHash<int,QVariant> _previewedProperties;
};

/**
 * A delegate which can display and edit color schemes in a view.
 */
class ColorSchemeViewDelegate : public QAbstractItemDelegate
{
public:
    ColorSchemeViewDelegate(QObject* parent = 0);

    // reimplemented
    virtual void paint(QPainter* painter, const QStyleOptionViewItem& option,
                       const QModelIndex& index) const;
    virtual QSize sizeHint( const QStyleOptionViewItem& option,
                       const QModelIndex& index) const;

   // virtual QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, 
   //                               const QModelIndex& index) const;
   // virtual bool editorEvent(QEvent* event,QAbstractItemModel* model,
   //                          const QStyleOptionViewItem& option, const QModelIndex& index);

};

/**
 * A delegate which can display and edit key bindings in a view.
 */
class KeyBindingViewDelegate : public QAbstractItemDelegate
{
public:
    KeyBindingViewDelegate(QObject* parent = 0);

    // reimplemented
    virtual void paint(QPainter* painter, const QStyleOptionViewItem& option,
                       const QModelIndex& index) const;
    virtual QSize sizeHint( const QStyleOptionViewItem& option,
                       const QModelIndex& index) const;

};

}
#endif // EDITSESSIONDIALOG_H
