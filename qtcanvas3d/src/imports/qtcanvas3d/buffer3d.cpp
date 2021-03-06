/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the QtCanvas3D module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL3$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPLv3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or later as published by the Free
** Software Foundation and appearing in the file LICENSE.GPL included in
** the packaging of this file. Please review the following information to
** ensure the GNU General Public License version 2.0 requirements will be
** met: http://www.gnu.org/licenses/gpl-2.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "buffer3d_p.h"

#include <QDebug>
#include <QString>

QT_BEGIN_NAMESPACE
QT_CANVAS3D_BEGIN_NAMESPACE

/*!
 * \qmltype Canvas3DBuffer
 * \since QtCanvas3D 1.0
 * \inqmlmodule QtCanvas3D
 * \brief Contains an OpenGL buffer.
 *
 * An uncreatable QML type that contains an OpenGL buffer. You can get it by calling the
 * \l{Context3D::createBuffer()}{Context3D.createBuffer()} method.
 */

/*!
 * \internal
 */
CanvasBuffer::CanvasBuffer(QObject *parent) :
    CanvasAbstractObject(parent),
    QOpenGLFunctions(),
    m_bindTarget(CanvasBuffer::UNINITIALIZED)
{
    initializeOpenGLFunctions();
    glGenBuffers(1, &m_bufferId);
}

/*!
 * \internal
 */
CanvasBuffer::CanvasBuffer(const CanvasBuffer& other) :
    CanvasAbstractObject(), // Copying a QObject, leave it parentless..
    QOpenGLFunctions(),
    m_bufferId(other.m_bufferId),
    m_bindTarget(other.m_bindTarget)
{
    initializeOpenGLFunctions();
}


/*!
 * \internal
 */
CanvasBuffer::~CanvasBuffer()
{
    // Crashes on exit as V4VM does it's final cleanup without checking of ownerships
    del();
}

/*!
 * \internal
 */
void CanvasBuffer::del()
{
    if (m_bufferId)
        glDeleteBuffers(1, &m_bufferId);
    m_bufferId = 0;
}

/*!
 * \internal
 */
bool CanvasBuffer::isAlive()
{
    return m_bufferId;
}

/*!
 * \internal
 */
CanvasBuffer::bindTarget CanvasBuffer::target()
{
    return m_bindTarget;
}

/*!
 * \internal
 */
void CanvasBuffer::setTarget(bindTarget bindPoint)
{
    //Q_ASSERT(m_bindTarget == CanvasBuffer::UNINITIALIZED);

    m_bindTarget = bindPoint;
}

/*!
 * \internal
 */
GLuint CanvasBuffer::id()
{
    return m_bufferId;
}

/*!
 * \internal
 */
QDebug operator<<(QDebug dbg, const CanvasBuffer *buffer)
{
    if (buffer)
        dbg.nospace() << "Canvas3DBuffer("<< buffer->name() <<", id:" << buffer->m_bufferId << ")";
    else
        dbg.nospace() << "Canvas3DBuffer("<< ((void*) buffer) <<")";
    return dbg.maybeSpace();
}

QT_CANVAS3D_END_NAMESPACE
QT_END_NAMESPACE
