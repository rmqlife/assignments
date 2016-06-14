package com.example.rmqmobile;

import java.io.File;

import android.app.Activity;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
import android.view.Display;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.ImageView;
import android.widget.Toast;

public class CameraActivity extends Activity {

	 final static int CAMERA_RESULT = 0;
	 ImageView imv;
	 String imageFilePath;
	 String imageDir;
	 Intent intentTakingPic;
	 File imageFile;
	 
	 final String SIMBOL_FILENAME="simbol.jpg";
	 
	 public void onCreate(Bundle savedInstanceState) 
	 {
	  super.onCreate(savedInstanceState);
	  setContentView(R.layout.activity_camera);
	  imageDir=Environment.getExternalStorageDirectory().getAbsolutePath()+
			  "/RMQMobile";
	  imageFilePath = Environment.getExternalStorageDirectory().getAbsolutePath()+
	  "/RMQMobile/myfavoritepicture.jpg";
	  File dir=new File(Environment.getExternalStorageDirectory().getAbsolutePath()+"/RMQMobile");
	  if (!dir.exists())
	  {
		  dir.mkdir();
	  }
	  Toast.makeText(getApplicationContext(), "will saved in:"+imageFilePath, 2*Toast.LENGTH_LONG).show();
	  
	  imageFile = new File(imageFilePath);
	  Uri imageFileUri = Uri.fromFile(imageFile);
	  
	  intentTakingPic = new Intent(android.provider.MediaStore.ACTION_IMAGE_CAPTURE);
	  intentTakingPic.putExtra(android.provider.MediaStore.EXTRA_OUTPUT, imageFileUri);
	  startActivityForResult(intentTakingPic, CAMERA_RESULT);
	 }
	    
	 
	 	private void takePicture()
	 	{
	 		startActivityForResult(intentTakingPic, CAMERA_RESULT);
	 	}
	 	
	 	private void save()//delete old and rename this
	 	{
	 		File file=new File(imageDir+File.separator+SIMBOL_FILENAME);
	 		if (file.exists())
	 		{
	 			file.delete();
	 		}
	 		
	 		imageFile.renameTo(file);
	 		this.cancel();
	 	}
	 	
	 	private void cancel()
	 	{
	 		this.finish();
	 	}
	 	
	 	
	    public boolean onCreateOptionsMenu(Menu menu) 
	    {
	        getMenuInflater().inflate(R.menu.activity_camera, menu);
	        return true;
	    }
	 	
		
		public boolean onOptionsItemSelected(MenuItem item) 
		{
			switch(item.getItemId())
			{
			case R.id.item_retake_pic:takePicture();break;
			case R.id.item_save_pic:save();break;
			case R.id.item_cancel:this.cancel();break;
			}
			return false;
		}
	 
		
		
		
		
	 protected void onActivityResult(int requestCode, int resultCode, Intent intent) 
	 {
	  super.onActivityResult(requestCode, resultCode, intent);
	  if (resultCode == RESULT_OK)
	  {
	   // Get a reference to the ImageView
	   imv = (ImageView) findViewById(R.id.imageView1);
	   Display currentDisplay = getWindowManager().getDefaultDisplay();
	   int dw = currentDisplay.getWidth();
	   int dh = currentDisplay.getHeight();
	   // Load up the image's dimensions not the image itself
	   
	   BitmapFactory.Options bmpFactoryOptions = new BitmapFactory.Options();
	   bmpFactoryOptions.inJustDecodeBounds = true;
	   
	   
	   Bitmap bmp = BitmapFactory.decodeFile(imageFilePath, bmpFactoryOptions);
	   int heightRatio = (int)Math.ceil(bmpFactoryOptions.outHeight/(float)dh);
	   int widthRatio = (int)Math.ceil(bmpFactoryOptions.outWidth/(float)dw);
	   Log.v("HEIGHTRATIO",""+heightRatio);
	   Log.v("WIDTHRATIO",""+widthRatio);
	   // If both of the ratios are greater than 1,
	   // one of the sides of the image is greater than the screen
	   if (heightRatio > 1 && widthRatio > 1)
	   {
		    if (heightRatio > widthRatio)
		    {
		     // Height ratio is larger, scale according to it
		     bmpFactoryOptions.inSampleSize = heightRatio;
		    }
		    else
		    {
		     // Width ratio is larger, scale according to it
		     bmpFactoryOptions.inSampleSize = widthRatio;
		    }
	   }
	   // Decode it for real
	   bmpFactoryOptions.inJustDecodeBounds = false;
	   bmp = BitmapFactory.decodeFile(imageFilePath, bmpFactoryOptions);
	   
	   // Display it
	   imv.setImageBitmap(bmp);
	  }
	 }
	}