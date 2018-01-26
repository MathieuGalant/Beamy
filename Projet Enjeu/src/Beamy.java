import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStreamReader;
import java.nio.file.DirectoryNotEmptyException;
import java.nio.file.Files;
import java.nio.file.NoSuchFileException;
import java.nio.file.Path;
import java.time.LocalTime;
import java.util.ArrayList;

public class Beamy
{
	private ArrayList<Alarm> alarmCollection;
	
	public Beamy() {
		alarmCollection = new ArrayList<Alarm>();
		start();
	}
	
	public void start(){
		
		
		System.out.println("What do you want to do ? ");
		boolean validCommand = false;
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String input="";
		
		while(!validCommand) {
			System.out.println("waiting order");
			
			try {
				input = br.readLine();
			} catch (IOException e) {
				e.printStackTrace();
			}
			
			
			if (input.equals("newAlarm")) { 
				System.out.println("newAlarm");
				this.newAlarm();
			}
			else if (input.equals("stop")) {
				System.out.println("stop");
				validCommand=true;
			}
			
			else if (input.equals("showAlarms")) {
				System.out.println(alarmCollection.toString());
			}
			else {
				System.out.println("try again");
			}
			
		}
		
		
		
	}
	
	public void newAlarm() {
		Alarm newAlarm = new Alarm();
		new Thread(newAlarm).start();
		alarmCollection.add(newAlarm);
		System.out.println("Une alarme a bien été créée.");
		
	}
	
	public void changeAlarmMusic(int argAlarmId, File argNewMusic)
	{
		//Permet de changer la musique d'un alarme. Cela demande de supprimer l'ancienne, d'en upload une autre, et d'indiquer sa position
		deleteFile(alarmCollection.get(argAlarmId).getMusicDirectory());
		downloadFile();
		alarmCollection.get(argAlarmId).setMusic(argNewMusic);
	}
	
	public void changeAlarmTime(int argAlarmId, LocalTime argNewTime) {
		//Change when the alarm will ring
		alarmCollection.get(argAlarmId).setTime(argNewTime);	
	}
	
	public void deleteFile(File file) {
		try {
		    Files.delete(file.toPath());
		} catch (NoSuchFileException x) {
		    System.err.format("%s: no such" + " file or directory%n", file);
		} catch (DirectoryNotEmptyException x) {
		    System.err.format("%s not empty%n", file);
		} catch (IOException x) {
		    // File permission problems are caught here.
		    System.err.println(x);
		}
	}
	
	public void downloadFile() {
		//TODO
	}
	public void displayAlarms() {
		
	}
	public void Alarm(){
		
	}
	
	public void AdjustVolume( )
	{
		
	}
	
	public void PlayMusic( )
	{
		
	}
	
	public void PlayNextMusic( )
	{
		
	}
	
	public void ChangeMusic( )
	{
		
	}
	
	public void PlayVideo( )
	{
		
	}
	
	public void ShowPhoneScreen( )
	{
		
	}
	
	public void StopVideo( )
	{
		
	}
	
	public void StopMusic( )
	{
		
	}
	
	public void SayResume( )
	{
		
	}
	
	public void RequestCode( )
	{
		
	}
	
	public void ProjectCode( )
	{
		
	}
	
	public void SendCode( )
	{
		
	}
	
	public void SaveConfiguration( )
	{
		
	}
	
	

	public void DeleteAlarm( )
	{
		
	}
	
	
	
	
	
	public void showDate( )
	{
		
	}
	
	
	public void PauseMusic( )
	{
		
	}
	
	
	public void ResumeMusic( )
	{
		
	}
	
	
	public void ResumeVideoFlux( )
	{
		
	}
	
	
	public void ResumeVideo( )
	{
		
	}
	
	
}
