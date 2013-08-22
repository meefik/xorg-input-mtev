# 
# Do NOT Edit the Auto-generated Part!
# Generated by: spectacle version 0.19
# 
# >> macros
# << macros

Name:       xf86-input-mtev
Summary:    Multitouch input driver for Xserver
Version:    0.1.13
Release:    1
Group:      System/X Hardware Support
License:    GPLv2
URL:        http://gitorious.org/xorg-next/xf86-input-mtev
Source0:    %{name}-%{version}.tar.gz
Source100:  xf86-input-mtev.yaml
BuildRequires:  pkgconfig(xorg-server)
BuildRequires:  pkgconfig(xkbfile)
BuildRequires:  pkgconfig(xproto)
BuildRequires:  pkgconfig(inputproto)
BuildRequires:  pkgconfig(xrandr)
BuildRequires:  pkgconfig(randrproto)
BuildRequires:  pkgconfig(xextproto)
BuildRequires:  pkgconfig(mtdev)


%description
- xf86-input-mtev - This package is a multitouch Xorg input driver
supporting MultiTouch protocol




%prep
%setup -q -n %{name}-%{version}

# >> setup
# << setup

%build
# >> build pre
# << build pre


make %{?jobs:-j%jobs}

# >> build post
# << build post
%install
rm -rf %{buildroot}
# >> install pre
# << install pre
%make_install 

# >> install post
# << install post






%files
%defattr(-,root,root,-)
/usr/lib/xorg/modules/input/mtev.so
# >> files
# << files

%changelog
 * Mon Dec 6 2010 James Ketrenos <jketreno@linux.intel.com> 0.1.13
 - Adapted to use libmtdev to support kernel protocol A and B
 * Wed Oct 27 2010 Mika Kuoppala <mika.kuoppala@nokia.com> 0.1.12
 -  Send motion events before button down
 * Tue Oct 26 2010 Mika Kuoppala <mika.kuoppala@nokia.com> 0.1.11
 - Added orientation config options: SwapAxes, InvertX, InvertY
 * Thu Sep 16 2010 Mika Kuoppala <mika.kuoppala@nokia.com> 0.1.10
 - First rpm release
