# libnss_log

A NSS-Library which logs all `hosts` requests to
`/tmp/nss-log-UID.log`.

# Usage

1. Install libnss_log
2. Add `log` to the `hosts` line in `/etc/nsswitch.conf`.

(Usually) the line should look like this:

```text
hosts: files log ...
```

Example log output:

```text
gethostbyname wpad
gethostbyname wpad
gethostbyname github.com
gethostbyname github.com
gethostbyname github.githubassets.com
gethostbyname github.githubassets.com
gethostbyname avatars1.githubusercontent.com
gethostbyname avatars1.githubusercontent.com
gethostbyname avatars2.githubusercontent.com
gethostbyname avatars2.githubusercontent.com
gethostbyname live.github.com
gethostbyname live.github.com
gethostbyname live.github.com
gethostbyname live.github.com
gethostbyname avatars0.githubusercontent.com
gethostbyname avatars0.githubusercontent.com
```

`wpad` is a name used by browsers to detect proxy settings (the more you know!).

# Installation

Requires `cmake`.

```bash
mkdir build
cd build
cmake ..
make
sudo make install
```
