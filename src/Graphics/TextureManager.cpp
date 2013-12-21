/************************************************************************
*
* Flood Project � (2008-201x)
* Licensed under the simplified BSD license. All rights reserved.
*
************************************************************************/

#include "Graphics/API.h"
#include "Graphics/TextureManager.h"
#include "Graphics/RenderBackend.h"
#include "Resources/ResourceManager.h"

NAMESPACE_GRAPHICS_BEGIN

//-----------------------------------//

TextureManager::TextureManager()
{
    ResourceManager* res = GetResourceManager();
    res->onResourceLoaded.Connect( this, &TextureManager::onLoaded );
    res->onResourceRemoved.Connect( this, &TextureManager::onUnloaded );
    res->onResourceReloaded.Connect( this, &TextureManager::onReloaded );
}

//-----------------------------------//

TextureManager::~TextureManager()
{
    ResourceManager* res = GetResourceManager();
    res->onResourceLoaded.Disconnect( this, &TextureManager::onLoaded );
    res->onResourceRemoved.Disconnect( this, &TextureManager::onUnloaded );
    res->onResourceReloaded.Disconnect( this, &TextureManager::onReloaded );

    #pragma TODO("Make sure all textures are released on exit")
    TextureMap::ConstIterator it;
    for( it = textures.Begin(); it != textures.End(); it++ )
    {
        const Texture* texture = it->second.get();
        //assert( texture->getReferenceCount() == 2 );
    }
}

//-----------------------------------//

void TextureManager::removeTexture(Image* image)
{
    TextureMap::Iterator it = textures.Find(image);
    
    if( it == textures.End() )
        return;

    textures.Erase(it);
}

//-----------------------------------//

static const uint8 TEX_SIZE = 64;

TexturePtr TextureManager::getTexture( const String& name )
{
    ResourceManager* res = GetResourceManager();
    ImageHandle handle = res->loadResource<Image>(name);
    return getTexture(handle);
}

//-----------------------------------//

TexturePtr TextureManager::getTexture( Image* image )
{
    if( !image )
    {
        // Image not valid.
        return nullptr;
    }

    // Image already has texture.
    else if( textures.Find(image) != textures.End() )
    {
        return textures[image];
    }

    // Image not loaded yet.
    else if( !image->isLoaded() ) 
    {
        Texture* texture = backend->createTexture();
        texture->allocate(Vector2i(TEX_SIZE, TEX_SIZE), PixelFormat::R8G8B8A8);

        textures[image] = texture;
        return texture;
    }

    return nullptr;
}

//-----------------------------------//

TexturePtr TextureManager::getTexture( const ImageHandle& imageHandle )
{
    Image* image = imageHandle.Resolve();

    if (TexturePtr texture = getTexture(image))
        return texture;

    // Create a new texture from image.
    Texture* texture = backend->createTexture();
    texture->setImage(imageHandle);

    textures[image] = texture;

    return texture;
}

//-----------------------------------//

void TextureManager::onLoaded( const ResourceEvent& event )
{
    ImageHandle handleImage = HandleCast<Image>(event.handle);
    Image* image = handleImage.Resolve();

    if( image->getResourceGroup() != ResourceGroup::Images )
        return;

    if( textures.Find(image) == textures.End() )
        return;

    Texture* texture = textures[image].get();
    texture->setImage(handleImage);

    backend->uploadTexture(texture);
}

//-----------------------------------//

void TextureManager::onUnloaded( const ResourceEvent& event )
{
    ImageHandle handleImage = HandleCast<Image>(event.handle);
    Image* image = handleImage.Resolve();

    if( image->getResourceGroup() != ResourceGroup::Images )
        return;

    if( textures.Find(image) == textures.End() )
        return;

    LogDebug( "Removing texture '%s'", image->getPath().CString() );

    removeTexture(image);
}

//-----------------------------------//

void TextureManager::onReloaded( const ResourceEvent& event )
{
    ImageHandle handleImage = HandleCast<Image>(event.handle);
    Image* newImage = handleImage.Resolve();

    if( newImage->getResourceGroup() != ResourceGroup::Images )
        return;
    
    Image* oldImage = (Image*) event.oldResource;

    if( textures.Find(oldImage) == textures.End() )
        return;

    LogDebug( "Reloading texture '%s'", newImage->getPath().CString() );

    Texture* texture = textures[oldImage].get();
    texture->setImage(handleImage);

    textures.Erase(oldImage);
    textures[newImage] = texture;
}

//-----------------------------------//

uint TextureManager::getMemoryUsage()
{
    uint total = 0;

    TextureMap::ConstIterator it;
    for( it = textures.Begin(); it != textures.End(); it++ )
        total += it->first->getBuffer().Size();

    return total;
}

//-----------------------------------//

NAMESPACE_GRAPHICS_END