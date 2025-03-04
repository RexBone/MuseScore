//=============================================================================
//  MuseScore
//  Music Composition & Notation
//
//  Copyright (C) 2019 MuseScore BVBA and others
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License version 2.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//=============================================================================

#include "google_analytics/ganalytics.h"
#include "settings/types/preferencekeys.h"
#include "telemetryservice.h"
#include "config.h"

TelemetryService::TelemetryService()
      {
      }

void TelemetryService::sendEvent(const QString &category, const QString &action, const QString &label, const QVariant &value, const QVariantMap &customValues)
      {
      if (!isTelemetryAllowed() || category.isEmpty() || action.isEmpty())
            return;

      GAnalytics::instance(TELEMETRY_TRACK_ID)->sendEvent(category, action, label, value, customValues);
      }

void TelemetryService::sendException(const QString &exceptionDescription, bool exceptionFatal, const QVariantMap &customValues)
      {
      if (!isTelemetryAllowed())
            return;

      GAnalytics::instance(TELEMETRY_TRACK_ID)->sendException(exceptionDescription, exceptionFatal, customValues);
      }

void TelemetryService::startSession()
      {
      if (!isTelemetryAllowed())
            return;

      GAnalytics::instance(TELEMETRY_TRACK_ID)->startSession();
      }

void TelemetryService::endSession()
      {
      if (!isTelemetryAllowed())
            return;

      GAnalytics::instance(TELEMETRY_TRACK_ID)->endSession();
      }

bool TelemetryService::isTelemetryAllowed() const
      {
#ifdef MSCORE_UNSTABLE
      return false;
#else
      return m_settings.value(PREF_APP_TELEMETRY_ALLOWED, false).toBool();
#endif
      }
