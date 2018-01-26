import java.io.File;
import java.net.URI;
import java.nio.file.Paths;
import java.time.Duration;
import java.time.LocalTime;

import javafx.embed.swing.JFXPanel;
import javafx.scene.media.Media;
import javafx.scene.media.MediaPlayer;

public class Alarm implements Runnable {

	private LocalTime alarmTime;
	private File alarmMusic;
	private String musicName; //TODO
	private File defaultMusicDirectory; //TODO
	
	public void run () {
	
		new JFXPanel(); //Useless, but necessary to avoid an error 
		defaultMusicDirectory = Paths.get(System.getProperty("user.home")+"\\Downloads\\alarmMusic.mp3").toFile();
		alarmTime=LocalTime.of(7,0); //On entre une heure par defaut 
		alarmMusic = defaultMusicDirectory;
		musicName = "DefaultMusic";
		start();
		
		
	}
	
	public void playMusic () {
		
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
		LocalTime localTime = LocalTime.now();
		long timeBeforeAlarm = Duration.between(localTime, alarmTime).toMillis();
		if (timeBeforeAlarm<0) {
			System.out.println(alarmTime + " and " + alarmTime.plusHours(24));	
			timeBeforeAlarm += 86400000;
		}
		//long timeBeforeAlarm = Math.abs(1000);
		System.out.println("Temps d'attente :"+timeBeforeAlarm);
		try {
			Thread.sleep(timeBeforeAlarm);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		playMusic();
	}

}
