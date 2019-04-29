# $Id: PKGBUILD 154170 2015-12-22 09:55:49Z spupykin $
# Maintainer: Sergej Pupykin <pupykin.s+arch@gmail.com>
# Contributor: Dag Odenhall <dag.odenhall@gmail.com>
# Contributor: Grigorios Bouzakis <grbzks@gmail.com>

pkgname=dwm
pkgver=6.2
pkgrel=1
pkgdesc="A dynamic window manager for X"
url="http://dwm.suckless.org"
arch=('i686' 'x86_64')
license=('MIT')
options=(zipman)
depends=('libx11' 'libxinerama' 'libxft' 'st')
install=dwm.install
source=(http://dl.suckless.org/dwm/dwm-$pkgver.tar.gz
	config.h
	dwm.desktop)

_patches=(01-push_no_master.diff
          02-attachaside.diff
          03-tilegap.diff
          04-removetitle.diff
          05-savefloats.diff
          06-schemes.diff
          )

source=(${source[@]} ${_patches[@]})

prepare() {
  cd $srcdir/$pkgname-$pkgver
  cp $srcdir/config.h config.h
}

build() {
  cd $srcdir/$pkgname-$pkgver

  echo "==> Applying Patches"
  for p in "${_patches[@]}"; do
    echo "  -> $p"
    patch < ../$p || return 1
  done

  make X11INC=/usr/include/X11 X11LIB=/usr/lib/X11
}

package() {
  cd $srcdir/$pkgname-$pkgver
  make PREFIX=/usr DESTDIR=$pkgdir install
  install -m644 -D LICENSE $pkgdir/usr/share/licenses/$pkgname/LICENSE
  install -m644 -D README $pkgdir/usr/share/doc/$pkgname/README
  install -m644 -D $srcdir/dwm.desktop $pkgdir/usr/share/xsessions/dwm.desktop
}

md5sums=('9929845ccdec4d2cc191f16210dd7f3d'
         'bc57881e9a35b84fe135fdf32aa188b6'
         '939f403a71b6e85261d09fc3412269ee'
         '70e2193234acdc57b688acbcf44bdbcf'
         'c75af619c04cfae7b9740ec140d1dc6c'
         'ead71425a73f08b3bdb8cfe5b48fbfbc'
         '5dfb8855df6996a4181fe1de47366b2d'
         'c2576b5b80958e76525473260bf09cc9'
         '5d4203b6ae49bd579799399976936146')
