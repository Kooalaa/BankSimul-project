package com.astru43.atm_app.util

import android.content.Context
import com.android.volley.Request
import com.android.volley.RequestQueue
import com.android.volley.toolbox.Volley

class NetUtil constructor(context: Context){ode
    companion object {
        @Volatile
        private var INSTANCE: NetUtil? = null
        fun getInstance(context: Context) =
            INSTANCE ?: synchronized(this) {
                INSTANCE ?: NetUtil(context).also {
                    INSTANCE = it
                }
            }
    }

    @Suppress("MemberVisibilityCanBePrivate")
    val requestQueue: RequestQueue by lazy {
        Volley.newRequestQueue(context.applicationContext)
    }

    fun <T> addRequest(req: Request<T>) {
        requestQueue.add(req)
    }
}