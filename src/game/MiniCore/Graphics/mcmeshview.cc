// This file belongs to the "MiniCore" game engine.
// Copyright (C) 2013 Jussi Lind <jussi.lind@iki.fi>
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
// MA  02110-1301, USA.
//

#include "mcmeshview.hh"

#include "mccamera.hh"
#include "mcglshaderprogram.hh"
#include "mcmesh.hh"
#include "mcmeshview.hh"

MCMeshView::MCMeshView(
    const std::string & viewId,
    MCMesh * mesh,
    bool batchMode)
: MCShapeView(viewId)
, m_mesh(mesh)
, m_batchMode(batchMode)
{}

MCMeshView::~MCMeshView()
{}

void MCMeshView::setMesh(MCMesh & mesh)
{
    m_mesh = &mesh;
}

MCMesh * MCMeshView::mesh() const
{
    return m_mesh;
}

void MCMeshView::setShaderProgram(MCGLShaderProgram * program)
{
    if (m_mesh)
    {
        m_mesh->setShaderProgram(program);
    }
}

void MCMeshView::setShadowShaderProgram(MCGLShaderProgram * program)
{
    if (m_mesh)
    {
        m_mesh->setShadowShaderProgram(program);
    }
}

void MCMeshView::render(const MCVector3d<MCFloat> & l, MCFloat angle, MCCamera * p)
{
    if (m_mesh)
    {
        m_mesh->setScale(1.0, 1.0, 1.0);
        m_mesh->render(p, l, angle, !m_batchMode);
    }
}

void MCMeshView::renderShadow(const MCVector3d<MCFloat> & l, MCFloat angle, MCCamera * p)
{
    if (m_mesh)
    {
        m_mesh->setScale(1.0, 1.0, 1.0);
        m_mesh->renderShadow(p, l, angle, !m_batchMode);
    }
}

void MCMeshView::renderScaled(const MCVector3d<MCFloat> & l, MCFloat angle,
    MCFloat w, MCFloat h, MCCamera * p)
{
    if (m_mesh)
    {
        m_mesh->setScale(w, h);
        m_mesh->render(p, l, angle, !m_batchMode);
    }
}

void MCMeshView::renderShadowScaled(const MCVector3d<MCFloat> & l,
    MCFloat angle, MCFloat w, MCFloat h, MCCamera * p)
{
    if (m_mesh)
    {
        m_mesh->setScale(w, h);
        m_mesh->renderShadow(p, l, angle, !m_batchMode);
    }
}

void MCMeshView::beginBatch()
{
    if (m_batchMode && m_mesh)
    {
        m_mesh->bind(true);
    }
}

void MCMeshView::endBatch()
{
    if (m_batchMode && m_mesh)
    {
        m_mesh->bind(false);
    }
}

void MCMeshView::beginShadowBatch()
{
    if (m_batchMode && m_mesh)
    {
        m_mesh->bindShadow(true);
    }
}

void MCMeshView::endShadowBatch()
{
    if (m_batchMode && m_mesh)
    {
        m_mesh->bindShadow(false);
    }
}

MCBBox<MCFloat> MCMeshView::bbox() const
{
    // TODO: Fix this! The view should know the angle of the
    // shape somehow. Now we just return a naive bbox.

    const MCFloat w = m_mesh->width() / 2;
    const MCFloat h = m_mesh->height() / 2;
    const MCFloat r = std::max(w, h);

    return MCBBox<MCFloat>(-r, -r, r, r);
}