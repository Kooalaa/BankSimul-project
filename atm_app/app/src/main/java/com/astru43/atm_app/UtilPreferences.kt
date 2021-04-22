package com.astru43.atm_app

import android.content.Context
import androidx.preference.PreferenceManager

class UtilPreferences {

    companion object {

        private const val TOKEN_ID = "com.astru43.atm_app.TOKEN"
        fun setToken(token: String, context: Context) {
            val editor = PreferenceManager.getDefaultSharedPreferences(context).edit()
            editor.putString(TOKEN_ID, token)
            editor.apply()
        }

        fun getToken(context: Context) : String {
            val preference = PreferenceManager.getDefaultSharedPreferences(context)
            return preference.getString(TOKEN_ID, "NULL")!!
        }

    }
}