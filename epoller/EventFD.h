/*
Copyright (C) 2016 iNuron NV

This file is part of Open vStorage Open Source Edition (OSE), as available from


    http://www.openvstorage.org and
    http://www.openvstorage.com.

This file is free software; you can redistribute it and/or modify it
under the terms of the GNU Affero General Public License v3 (GNU AGPLv3)
as published by the Free Software Foundation, in version 3 as it comes
in the <LICENSE.txt> file of the Open vStorage OSE distribution.

Open vStorage is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY of any kind.
*/
#pragma once

#include <iostream>
#include <sys/eventfd.h>

struct EventFD {

  EventFD() {

    evfd_ = eventfd(0, EFD_CLOEXEC | EFD_SEMAPHORE | EFD_NONBLOCK);
    if (evfd_ < 0) {
      throw std::runtime_error("failed to create eventfd");
    }
  }

  ~EventFD() {
    if (evfd_ != -1) {
      close(evfd_);
    }
  }

  EventFD(const EventFD &) = delete;

  EventFD &operator=(const EventFD &) = delete;

  int getfd() const {
    return evfd_;
  }

  eventfd_t lastValue() const {
    return lastValue_;
  }

  int readfd(uint64_t ctx) {

    int ret = 0;

    eventfd_t readValue;
    do {
      ret = eventfd_read(evfd_, &readValue);
    } while (ret < 0 && (errno == EINTR));

    if (ret == 0) { 
      lastValue_ = readValue;
    } else if (errno != EAGAIN) {
      // eagain signals call would block
      LOG(ERROR) << "eventfd read failed with errno=" << errno;
      ret = -errno;
    } 

    return ret;
  }

  int writefd() {

    uint64_t u = 1;

    int ret;

    do {
      ret = eventfd_write(evfd_, static_cast<eventfd_t>(u));
    } while (ret < 0 && (errno == EINTR || errno == EAGAIN));
    if (ret < 0) {
      ret = -1;
    }
    return ret;
  }

private:
  int evfd_ = -1;
  eventfd_t lastValue_ = 0;
};

