#include "../include/MajorSelect.hpp"

MajorSelect::MajorSelect(Vector2f pos, const EntityInfo &idleOptionImageInfo, const EntityInfo &selectOptionImageInfo,
                         const EntityInfo &optionTextInfo, float scaleFactor)
    : pos(pos), idleImgTexture(idleOptionImageInfo.texture), selectImgTexture(selectOptionImageInfo.texture),
      textTexture(optionTextInfo.texture) {

    this->imgSrcRect = {0, 0, idleOptionImageInfo.w, idleOptionImageInfo.h};
    this->textSrcRect = {0, 0, optionTextInfo.w, optionTextInfo.h};
    this->major = optionTextInfo.text;

    setDstRect(imgSrcRect, imgDstRect, scaleFactor);
    setDstRect(textSrcRect, textDstRect, scaleFactor * 0.6f);
}

bool MajorSelect::collide(SDL_FPoint mousePos) {
    if (SDL_PointInFRect(&mousePos, &imgDstRect)) {
        return true;
    }
}

void MajorSelect::setDstRect(SDL_Rect srcRect, SDL_FRect &dstRect, float scale) {
    dstRect.w = (float) srcRect.w * scale;
    dstRect.h = (float) srcRect.h * scale;
    pos = {pos.x - dstRect.w / 2, pos.y};
    dstRect.x = pos.x;
    dstRect.y = pos.y;
}

void MajorSelect::setTextPos() {
    textDstRect.x = pos.x + imgDstRect.w / 2;
    textDstRect.y = pos.y + imgDstRect.h / 2 - textDstRect.h / 2;
}

void MajorSelect::draw(SDL_Renderer *renderer) {
    setTextPos();
    selected ? currImgTexture = selectImgTexture : currImgTexture = idleImgTexture;
    SDL_RenderCopyF(renderer, currImgTexture, &imgSrcRect, &imgDstRect);
    SDL_RenderCopyF(renderer, textTexture, &textSrcRect, &textDstRect);
}