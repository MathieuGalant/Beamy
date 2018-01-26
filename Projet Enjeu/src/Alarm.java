import java.io.File;
import java.net.URI;
import java.nio.file.Paths;
import java.time.Duration;
import java.time.LocalTime;

import javafx.embed.swing.JFXPanel;
import javafx.scene.media.Media;
import javafx.scene.media.MediaPlayer;

public class Alarm implements Runnable {

	private LocalTime alarmTime; // When the alarm will ring
	private File alarmMusic; // The music linked to the alarm
	private String musicName; //TODO
	private File defaultMusicDirectory; // The default music
	
	public void run () { // Initialization 
		
		//Useless, but necessary to avoid an error 
		new JFXPanel(); 
		// Define the default music :
		defaultMusicDirectory = Paths.get(System.getProperty("user.home")+"\\Downloads\\alarmMusic.mp3").toFile();
		// The default music is assigned 
		alarmMusic = defaultMusicDirectory;
		// Define the default hour when the alarm will ring
		alarmTime=LocalTime.of(7,0);
		//Music name. Perhaps useless.
		musicName = "DefaultMusic";
		// Execute the method start
		start();
		
		
	}
	
	public void playMusic () {
		//Catch the Music's URL, create a Media with it, and play it
		URI u = alarmMusic.toURI();
		Media alarmMusic = new Media(u.toString());
		MediaPlayer mediaPlayer = new MediaPlayer(alarmMusic);
		mediaPlayer.play();
	}
	
	public void setTime(LocalTime argNewTime) {
			alarmTime = argNewTime;
	}
	
	public void setMusic(File argMusicDirectory) {
		alarmMusic=argMusicDirectory;
	}
	
	public String toString() {
		return ("Une alarme est réglée pour "+alarmTime.toString()+" avec comme sonnerie " + musicName);
	}
	
	public File getMusicDirectory() {
		return alarmMusic;
	}
	
	public void setMusicDirectory(File newMusicDirectory) {
		alarmMusic = newMusicDirectory;
	}
	
	public void start() {
		//Catch the actual hour
		LocalTime localTime = LocalTime.now();
		//Get the difference the actual hour and the alarm hour. Output a long in Milliseconds
		long timeBeforeAlarm = Duration.between(localTime, alarmTime).toMillis();
		//If alarm hour passed, return a negative number. We need to add a complete day.
		//Exemple :Will return -2 between AlarmTime = 7 and Actual Time = 9. +24 = 22 hours, now correct.
		if (timeBeforeAlarm<0) {
			timeBeforeAlarm += 86400000;
		}
		//long timeBeforeAlarm = Math.abs(1000);
		System.out.println("Temps d'attente :"+timeBeforeAlarm + "en millisecondes");
		try {
			// The threat sleep until it need to ring. PROBLEM: Can't execute method during the sleep ?
			//Possible solution : Make here another threat just to ring, that we overwrite everyone a method is called here
			Thread.sleep(timeBeforeAlarm);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		// Execute the method PlayMusic
		playMusic();
	}

}
