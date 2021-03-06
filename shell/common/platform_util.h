// Copyright (c) 2013 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef SHELL_COMMON_PLATFORM_UTIL_H_
#define SHELL_COMMON_PLATFORM_UTIL_H_

#include <string>

#include "base/callback_forward.h"
#include "base/files/file_path.h"
#include "build/build_config.h"

#if defined(OS_WIN)
#include "base/strings/string16.h"
#endif

class GURL;

namespace platform_util {

typedef base::OnceCallback<void(const std::string&)> OpenExternalCallback;

// Show the given file in a file manager. If possible, select the file.
// Must be called from the UI thread.
void ShowItemInFolder(const base::FilePath& full_path);

// Open the given file in the desktop's default manner.
// Must be called from the UI thread.
bool OpenItem(const base::FilePath& full_path);

struct OpenExternalOptions {
  bool activate = true;
  base::FilePath working_dir;
};

// Open the given external protocol URL in the desktop's default manner.
// (For example, mailto: URLs in the default mail user agent.)
void OpenExternal(const GURL& url,
                  const OpenExternalOptions& options,
                  OpenExternalCallback callback);

// Move a file to trash.
bool MoveItemToTrash(const base::FilePath& full_path, bool delete_on_fail);

void Beep();

#if defined(OS_MACOSX)
bool GetLoginItemEnabled();
bool SetLoginItemEnabled(bool enabled);
#endif

#if defined(OS_LINUX)
// Returns a success flag.
// Unlike libgtkui, does *not* use "chromium-browser.desktop" as a fallback.
bool GetDesktopName(std::string* setme);
#endif

}  // namespace platform_util

#endif  // SHELL_COMMON_PLATFORM_UTIL_H_
