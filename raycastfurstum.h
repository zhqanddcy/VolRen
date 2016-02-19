#ifndef RAYCASTFURSTUM_H
#define RAYCASTFURSTUM_H

#include <memory>
#include <QMatrix4x4>
#include "raycastcube.h"

namespace yy {
namespace volren {

class IRaycastFrustum
{
public:
    virtual int texWidth() const = 0;
    virtual int texHeight() const = 0;
    virtual QMatrix4x4 matModel() const = 0;
    virtual QMatrix4x4 matView() const = 0;
    virtual QMatrix4x4 matProj() const = 0;

    virtual void setTexSize(int w, int h) = 0;
    virtual void setVolSize(int w, int h, int d) = 0;
    virtual void setMatView(const QMatrix4x4& matView) = 0;
    virtual void setMatProj(const QMatrix4x4& matProj) = 0;
    virtual void setMatVP(const QMatrix4x4& matView, const QMatrix4x4& matProj) { setMatView(matView); setMatProj(matProj); }

    virtual std::shared_ptr<GLuint> texEntry() const = 0;
    virtual std::shared_ptr<GLuint> texExit() const = 0;
};

class RaycastFrustum : public virtual IRaycastFrustum
{
public:
    RaycastFrustum();
    virtual ~RaycastFrustum();

    virtual int texWidth() const { return _texWidth; }
    virtual int texHeight() const { return _texHeight; }
    virtual QMatrix4x4 matModel() const;
    virtual QMatrix4x4 matView() const { return _matView; }
    virtual QMatrix4x4 matProj() const { return _matProj; }

    virtual void setTexSize(int w, int h);
    virtual void setVolSize(int w, int h, int d);
    virtual void setMatView(const QMatrix4x4 &matView);
    virtual void setMatProj(const QMatrix4x4 &matProj);

    virtual std::shared_ptr<GLuint> texEntry() const;
    virtual std::shared_ptr<GLuint> texExit() const;

private:
    void initializeGL() const;
    void updateCube() const;
    void newFBOs() const;
    void newFBO(int w, int h, std::shared_ptr<GLuint>* fbo, std::shared_ptr<GLuint>* tex, std::shared_ptr<GLuint>* ren) const;
    void makeEntry() const;
    void makeExit() const;

private:
    const int _defaultFBOSize = 480;
    mutable RaycastCube _cube;
    mutable std::shared_ptr<Painter> _pNear, _pFar;
    mutable std::shared_ptr<GLuint> _entryFBO, _exitFBO;
    mutable std::shared_ptr<GLuint> _entryTex, _exitTex;
    mutable std::shared_ptr<GLuint> _entryRen, _exitRen;
    mutable Shape _plane;
    mutable bool _isFBOUpdated, _isCubeUpdated, _isGLInitialized, _isEntryUpdated, _isExitUpdated;
    QMatrix4x4 _matView, _matProj;
    int _texWidth, _texHeight;
    int _volWidth, _volHeight, _volDepth;
};

//// TODO: implement frustum with CUDA
//class RaycastFurstum
//{
//public:
//    RaycastFurstum();
//    ~RaycastFurstum();

//    void initializeGL();
//    // setResolution changes the texture pointers
//    void setResolution(int w, int h);
//    int getTextureWidth() const { return texWidth; }
//    int getTextureHeight() const { return texHeight; }
//    void setVolumeDimension(int w, int h, int d);
//    const QMatrix4x4& modelMatrix() { return cube.matrix(); }
//    // a getter that doesn't render a new texture
//    std::shared_ptr<GLuint> entryTexture() const { return entryTex; }
//    // providing view and projection matrix will render a new texture
//    std::shared_ptr<GLuint> entryTexture(const QMatrix4x4& v, const QMatrix4x4& p);
//    // a getter that doesn't render a new texture
//    std::shared_ptr<GLuint> exitTexture() const { return exitTex; }
//    // providing view and projection matrix will render a new texture
//    std::shared_ptr<GLuint> exitTexture(const QMatrix4x4& v, const QMatrix4x4& p);

//protected:

//private:
//    const int defaultFBOSize = 480;
//    RaycastCube cube;
//    std::shared_ptr<GLuint> entryFBO, exitFBO;
//    std::shared_ptr<GLuint> entryTex, exitTex;
//    std::shared_ptr<GLuint> entryRen, exitRen;
//    Shape plane;
//    Painter pNear, pFar;
//    int texWidth, texHeight;
//    int volWidth, volHeight, volDepth;

//    void newFBOs();
//    void newFBO(int w, int h, std::shared_ptr<GLuint>* fbo, std::shared_ptr<GLuint>* tex, std::shared_ptr<GLuint>* ren) const;

//};

} // namespace volren
} // namespace yy

#endif // RAYCASTFURSTUM_H
