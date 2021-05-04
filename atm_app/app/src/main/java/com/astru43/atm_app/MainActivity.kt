package com.astru43.atm_app

import android.annotation.SuppressLint
import android.content.Intent
import android.content.pm.PackageManager
import android.os.Bundle
import android.os.VibrationEffect
import android.os.Vibrator
import android.text.Editable
import android.util.Log
import android.view.Menu
import android.view.MenuInflater
import android.view.MenuItem
import android.widget.Button
import android.widget.EditText
import android.widget.TextView
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import androidx.camera.view.PreviewView
import androidx.core.app.ActivityCompat
import androidx.core.content.ContextCompat
import com.android.volley.Request
import com.android.volley.toolbox.JsonObjectRequest
import com.astru43.atm_app.util.CameraUtil
import com.astru43.atm_app.util.NetUtil
import com.astru43.atm_app.util.PrefUtil
import org.json.JSONException
import org.json.JSONObject
import java.util.*
import java.util.concurrent.ExecutorService
import java.util.concurrent.Executors

class MainActivity : AppCompatActivity() {

    companion object {
        const val PERMISSION_REQUEST: Int = 10
    }

    private lateinit var previewView: PreviewView
    private lateinit var cameraExecutor: ExecutorService
    private lateinit var cameraUtil: CameraUtil


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        setSupportActionBar(findViewById(R.id.toolbar))

        val sendButton: Button = findViewById(R.id.button)
        sendButton.setOnClickListener {
            val inputId: EditText = findViewById(R.id.inputId)
            val textView: TextView = findViewById(R.id.response)

            when {
                PrefUtil.getToken(this).toUpperCase(Locale.ROOT) == "NULL" -> {
                    Toast.makeText(this, "No mobile token registered", Toast.LENGTH_SHORT).show()
                }
                inputId.text.length == 43 -> {
                    var url = "http://astru.ddns.net:8080/mobile/mobile"
                    url += "/" + inputId.text.toString()

                    val request = JsonObjectRequest(Request.Method.GET, url, null, { response ->
                        //@SuppressLint("SetTextI18n")
                        //textView.text = "Response: %s".format(response)

                        val intent = Intent(this, AcceptLogin::class.java)
                            .putExtra("com.astru43.atm_app.ATM_TOKEN", inputId.text.toString())
                        startActivity(intent)
                        inputId.text = Editable.Factory().newEditable("")

                    }, { error ->
                        if (error?.networkResponse?.statusCode == 404) {
                            try {
                                val obj =
                                    JSONObject(error.networkResponse.data.toString(charset("utf-8")))
                                //textView.text = obj.getString("error")
                                Toast.makeText(this, obj.getString("error"), Toast.LENGTH_SHORT)
                                    .show()
                                Log.i("NotFound", error.networkResponse.statusCode.toString())
                                Log.i("NotFoundResponse", obj.toString())
                            } catch (e: JSONException) {
                                Log.e("ParseJson", "Could not parse json data")
                            }
                        }
                    })

                    NetUtil.getInstance(this).addRequest(request)
                }
                else -> {
                    Toast.makeText(this, "No valid token provided", Toast.LENGTH_SHORT).show()
                }
            }
        }


        previewView = findViewById(R.id.Preview_main)
        cameraExecutor = Executors.newSingleThreadExecutor()

        if (!allPermissionsGranted()) {
            ActivityCompat.requestPermissions(
                this, arrayOf(android.Manifest.permission.CAMERA), PERMISSION_REQUEST
            )
        }
    }


    private val cameraOutputHandler: (String) -> Unit = { data ->
        val editText: EditText = findViewById(R.id.inputId)
        val editableData = Editable.Factory().newEditable(data)
        if (data != editText.text.toString()) {
            editText.text = editableData
            val vibrator = getSystemService(VIBRATOR_SERVICE) as Vibrator
            if (vibrator.hasVibrator()) {
                val vibrationEffect: VibrationEffect = VibrationEffect.createOneShot(1, 1)
                vibrator.vibrate(vibrationEffect)
            }
        }
    }

    private fun allPermissionsGranted() = arrayOf(android.Manifest.permission.CAMERA).all {
        ContextCompat.checkSelfPermission(
            baseContext, it
        ) == PackageManager.PERMISSION_GRANTED
    }

    override fun onRequestPermissionsResult(
        requestCode: Int,
        permissions: Array<String>,
        grantResults: IntArray
    ) {
        if (requestCode == PERMISSION_REQUEST) {
            if (!allPermissionsGranted()) {
                Toast.makeText(
                    this,
                    "Permissions not granted by the user.",
                    Toast.LENGTH_SHORT
                ).show()
            }
        }
    }

    override fun onCreateOptionsMenu(menu: Menu?): Boolean {
        super.onCreateOptionsMenu(menu)
        val inflater: MenuInflater = menuInflater
        inflater.inflate(R.menu.main_menu, menu)
        return true
    }

    override fun onOptionsItemSelected(item: MenuItem): Boolean {
        return when (item.itemId) {
            R.id.token -> {
                val intent = Intent(this, AddToken::class.java)
                startActivity(intent)
                true
            }
            else -> super.onOptionsItemSelected(item)
        }


    }

    override fun onResume() {
        super.onResume()
        cameraUtil = CameraUtil(this, previewView, cameraExecutor, cameraOutputHandler)
    }

    override fun onDestroy() {
        super.onDestroy()
        cameraExecutor.shutdown()
    }
}