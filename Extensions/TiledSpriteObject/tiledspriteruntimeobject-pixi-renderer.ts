namespace gdjs {
  import PIXI = GlobalPIXIModule.PIXI;

  class TiledSpriteRuntimeObjectPixiRenderer {
    _object: gdjs.TiledSpriteRuntimeObject;
    _tiledSprite: PIXI.TilingSprite;

    constructor(
      runtimeObject: gdjs.TiledSpriteRuntimeObject,
      runtimeScene: gdjs.RuntimeScene,
      textureName: string
    ) {
      this._object = runtimeObject;
      const texture = runtimeScene
        .getGame()
        .getImageManager()
        .getPIXITexture(textureName);
      this._tiledSprite = new PIXI.TilingSprite(texture, 1024, 1024);

      runtimeScene
        .getLayer('')
        .getRenderer()
        .addRendererObject(this._tiledSprite, runtimeObject.getZOrder());
      this.updatePosition();
      this.updateAngle();
      this.updateXOffset();
      this.updateYOffset();
    }

    getRendererObject() {
      return this._tiledSprite;
    }

    updateOpacity(): void {
      this._tiledSprite.alpha = this._object.opacity / 255;
    }

    updatePosition(): void {
      this._tiledSprite.position.x =
        this._object.x + this._tiledSprite.width / 2;
      this._tiledSprite.position.y =
        this._object.y + this._tiledSprite.height / 2;
    }

    setTexture(textureName, runtimeScene): void {
      const texture = runtimeScene
        .getGame()
        .getImageManager()
        .getPIXITexture(textureName);
      this._tiledSprite.texture = texture;
      this.updatePosition();
    }

    updateAngle(): void {
      this._tiledSprite.rotation = gdjs.toRad(this._object.angle);
    }

    getWidth(): float {
      return this._tiledSprite.width;
    }

    getHeight(): float {
      return this._tiledSprite.height;
    }

    setWidth(width): void {
      this._tiledSprite.width = width;
      this._tiledSprite.pivot.x = width / 2;
      this.updatePosition();
    }

    setHeight(height): void {
      this._tiledSprite.height = height;
      this._tiledSprite.pivot.y = height / 2;
      this.updatePosition();
    }

    updateXOffset(): void {
      // Known PIXI.js issue, the coordinates should not exceed the width/height of the texture,
      // otherwise the texture will be pixelated over time.
      // See https://github.com/pixijs/pixijs/issues/7891#issuecomment-947549553
      this._tiledSprite.tilePosition.x =
        -this._object._xOffset % this._tiledSprite.texture.width;
    }

    updateYOffset(): void {
      // Known PIXI.js issue, the coordinates should not exceed the width/height of the texture,
      // otherwise the texture will be pixelated over time.
      // See https://github.com/pixijs/pixijs/issues/7891#issuecomment-947549553
      this._tiledSprite.tilePosition.y =
        -this._object._yOffset % this._tiledSprite.texture.height;
    }

    setColor(rgbColor): void {
      const colors = rgbColor.split(';');
      if (colors.length < 3) {
        return;
      }
      // @ts-expect-error ts-migrate(2322) FIXME: Type 'string' is not assignable to type 'number'.
      this._tiledSprite.tint =
        '0x' +
        gdjs.rgbToHex(
          parseInt(colors[0], 10),
          parseInt(colors[1], 10),
          parseInt(colors[2], 10)
        );
    }

    getColor() {
      const rgb = PIXI.utils.hex2rgb(this._tiledSprite.tint);
      return (
        Math.floor(rgb[0] * 255) +
        ';' +
        Math.floor(rgb[1] * 255) +
        ';' +
        Math.floor(rgb[2] * 255)
      );
    }

    getTextureWidth() {
      return this._tiledSprite.texture.width;
    }

    getTextureHeight() {
      return this._tiledSprite.texture.height;
    }
  }

  export const TiledSpriteRuntimeObjectRenderer = TiledSpriteRuntimeObjectPixiRenderer;
  export type TiledSpriteRuntimeObjectRenderer = TiledSpriteRuntimeObjectPixiRenderer;
}
