﻿/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
****************************************************************************/

#pragma once

#include "icontext.h"
#include "icore.h"

#include <utils/appmainwindow.h>
#include <utils/dropsupport.h>

#include <QColor>
#include <QMap>

#include <functional>

QT_BEGIN_NAMESPACE
class QPrinter;
class QToolButton;
QT_END_NAMESPACE

namespace Core
{

class InfoBar;
class ModeManager;
enum class Side;
class SettingsDatabase;

namespace Internal
{

class FancyTabWidget;
class GeneralSettings;
class VersionDialog;
class WindowSupport;
//class SystemEditor;

class MainWindow : public Utils::AppMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow() override;

    void init();
    void extensionsInitialized();
    void aboutToShutdown();

    IContext* contextObject(QWidget* widget);
    void      addContextObject(IContext* context);
    void      removeContextObject(IContext* context);

    inline SettingsDatabase* settingsDatabase() const { return m_settingsDatabase; }
    virtual QPrinter*        printer() const;
    IContext*                currentContextObject() const;
    QStatusBar*              statusBar() const;
    InfoBar*                 infoBar() const;

    void updateAdditionalContexts(const Context& remove, const Context& add,
                                  ICore::ContextPriority priority);

    void setOverrideColor(const QColor& color);

    QStringList additionalAboutInformation() const;
    void        appendAboutInformation(const QString& line);

    void addPreCloseListener(const std::function<bool()>& listener);

    void saveSettings();

    void restart();

public slots:
    void exit();

protected:
    void closeEvent(QCloseEvent* event) override;

private:
    void aboutQtCreator();
    void aboutPlugins();
    void updateFocusWidget(QWidget* old, QWidget* now);
    void destroyVersionDialog();
    void openDroppedFiles(const QList<Utils::DropSupport::FileSpec>& files);
    void restoreWindowState();

    void updateContextObject(const QList<IContext*>& context);
    void updateContext();

    void registerDefaultContainers();
    void registerDefaultActions();
    void registerModeSelectorStyleActions();

    void readSettings();
    void saveWindowSettings();

    void updateModeSelectorStyleMenu();

    ICore*            m_coreImpl = nullptr;
    QStringList       m_aboutInformation;
    Context           m_highPrioAdditionalContexts;
    Context           m_lowPrioAdditionalContexts;
    SettingsDatabase* m_settingsDatabase = nullptr;
    mutable QPrinter* m_printer          = nullptr;
    WindowSupport*    m_windowSupport    = nullptr;

    ModeManager*    m_modeManager   = nullptr;
    FancyTabWidget* m_modeStack     = nullptr;
    VersionDialog*  m_versionDialog = nullptr;

    QList<IContext*> m_activeContext;

    QMap<QWidget*, IContext*> m_contextWidgets;

    GeneralSettings* m_generalSettings = nullptr;

    // actions
    QAction* m_exitAction                             = nullptr;
    QAction* m_optionsAction                          = nullptr;
    QAction* m_cycleModeSelectorStyleAction           = nullptr;
    QAction* m_setModeSelectorStyleIconsAndTextAction = nullptr;
    QAction* m_setModeSelectorStyleHiddenAction       = nullptr;
    QAction* m_setModeSelectorStyleIconsOnlyAction    = nullptr;
    QAction* m_themeAction                            = nullptr;

    QToolButton*                 m_toggleLeftSideBarButton  = nullptr;
    QToolButton*                 m_toggleRightSideBarButton = nullptr;
    QColor                       m_overrideColor;
    QList<std::function<bool()>> m_preCloseListeners;
};

} // namespace Internal
} // namespace Core
