# $Id: PKGBUILD 154170 2015-12-22 09:55:49Z spupykin $
# Maintainer: Sergej Pupykin <pupykin.s+arch@gmail.com>
# Contributor: Dag Odenhall <dag.odenhall@gmail.com>
# Contributor: Grigorios Bouzakis <grbzks@gmail.com>

pkgname=dwm
pkgver=6.1
pkgrel=3
pkgdesc="A dynamic window manager for X"
url="http://dwm.suckless.org"
arch=('i686' 'x86_64')
license=('MIT')
options=(zipman)
depends=('libx11' 'libxinerama' 'libxft' 'freetype2' 'st')
install=dwm.install
source=(http://dl.suckless.org/dwm/dwm-$pkgver.tar.gz
	config.h
        push.c
        bstack.c
        gaplessgrid.c
	dwm.desktop)

_patches=(01-scratchpad.diff
          02-savefloats.diff
          03-statuscolors.diff
          04-attachaside.diff
          05-tilegap.diff
          )

source=(${source[@]} ${_patches[@]})

prepare() {
  cd $srcdir/$pkgname-$pkgver
  cp $srcdir/config.h config.h
  cp $srcdir/push.c push.c
  cp $srcdir/bstack.c bstack.c
  cp $srcdir/gaplessgrid.c gaplessgrid.c
}

build() {
  cd $srcdir/$pkgname-$pkgver

  echo "==> Applying Patches"
  for p in "${_patches[@]}"; do
    echo "  -> $p"
    patch < ../$p || return 1
  done

  make X11INC=/usr/include/X11 X11LIB=/usr/lib/X11 FREETYPEINC=/usr/include/freetype2
}

package() {
  cd $srcdir/$pkgname-$pkgver
  make PREFIX=/usr DESTDIR=$pkgdir install
  install -m644 -D LICENSE $pkgdir/usr/share/licenses/$pkgname/LICENSE
  install -m644 -D README $pkgdir/usr/share/doc/$pkgname/README
  install -m644 -D $srcdir/dwm.desktop $pkgdir/usr/share/xsessions/dwm.desktop
}

md5sums=('f0b6b1093b7207f89c2a90b848c008ec'
         'c94b4dfb5253f84ed1839334d0e5de99'
         '689534c579b1782440ddcaf71537d8fd'
         '362e07f0f042875b84d7739d9d8855c4'
         '4ba509b3b93f7b1418dc703c70de536f'
         '939f403a71b6e85261d09fc3412269ee'
         'c28d9aba178490b4188158bc24159cdb'
         '103805203b6f34cfcba7477d57bd98f2'
         'ed406bed8c3278d99d3ff556f5f4f228'
         'e67fab561c52b8380050130350fe0267'
         '3c0e4dd2f569d974233d559f34a11be8')
