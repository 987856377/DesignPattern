#pragma once
/*

��ͼ����һ����Ľӿ�ת���ɿͻ�ϣ��������һ���ӿڡ�������ģʽʹ��ԭ�����ڽӿڲ����ݶ�����һ��������Щ�����һ������
��Ҫ�������Ҫ��������ϵͳ�У�����Ҫ��һЩ"�ִ�Ķ���"�ŵ��µĻ����У����»���Ҫ��Ľӿ����ֶ���������ġ�
��ʱʹ�ã� 1��ϵͳ��Ҫʹ�����е��࣬������Ľӿڲ�����ϵͳ����Ҫ�� 
			2����Ҫ����һ�������ظ�ʹ�õ��࣬������һЩ�˴�֮��û��̫�������һЩ�࣬����һЩ�����ڽ�����������һ��������ЩԴ�಻һ����һ�µĽӿڡ� 
			3��ͨ���ӿ�ת������һ���������һ����ϵ�С��������ϻ��ͷ��ݣ����ڶ���һ���ɻ����ڲ�����ʵ��������£�����һ�������������������һ��������ʵ�ַɵĽӿڡ���
��ν�����̳л��������Ƽ�����
�ؼ����룺�������̳л��������еĶ���ʵ����Ҫ��Ŀ��ӿڡ�
Ӧ��ʵ���� 1���������� 110V���й� 220V����Ҫ��һ���������� 110V ת��Ϊ 220V�� 
			2��JAVA JDK 1.1 �ṩ�� Enumeration �ӿڣ����� 1.2 ���ṩ�� Iterator �ӿڣ���Ҫʹ�� 1.2 �� JDK����Ҫ����ǰϵͳ�� Enumeration �ӿ�ת��Ϊ Iterator �ӿڣ���ʱ����Ҫ������ģʽ�� 
			3���� LINUX ������ WINDOWS ���� 
			4��JAVA �е� jdbc��
�ŵ㣺 1���������κ�����û�й�������һ�����С� 
		2���������ĸ��á� 
		3�����������͸���ȡ� 
		4������Ժá�
ȱ�㣺 1�������ʹ��������������ϵͳ�ǳ����ң�����������а��ա�
		  ���磬�����������õ��� A �ӿڣ���ʵ�ڲ���������� B �ӿڵ�ʵ�֣�һ��ϵͳ���̫��������������������һ�����ѡ����������Ǻ��б�Ҫ�����Բ�ʹ��������������ֱ�Ӷ�ϵͳ�����ع��� 
		2.���� JAVA ����̳�һ���࣬��������ֻ������һ���������࣬����Ŀ��������ǳ����ࡣ
ʹ�ó������ж������޸�һ���������е�ϵͳ�Ľӿڣ���ʱӦ�ÿ���ʹ��������ģʽ��
ע�������������������ϸ���ʱ��ӵģ����ǽ�����ڷ��۵���Ŀ�����⡣

*/

class MediaPlayer {
public:
	virtual void play(string audioType,string filename) = 0;
};

class AdvancedMediaPlayer {
public:
	virtual void playVlc(string name) = 0;
	virtual void playMp4(string name) = 0;
};

class VlcPlayer : public AdvancedMediaPlayer {
public:
	void playVlc(string name) {
		std::cout << "playing Vlc: " << name.data() << std::endl;
	}
	void playMp4(string name) {

	}
};

class Mp4Player : public AdvancedMediaPlayer {
public:
	void playMp4(string name) {
		std::cout << "playing Mp4: " << name.data() << std::endl;
	}

	void playVlc(string name) {

	}
};

class MediaAdapter : public MediaPlayer {
public:
	explicit MediaAdapter(string audioType) {
		if (audioType._Equal("MP4"))
		{			
			advancedMediaPlayer = new Mp4Player;
		}
		else if(audioType._Equal("VLC"))
		{
			advancedMediaPlayer = new VlcPlayer;
		}
	}

	void play(string audioType, string filename) {
		if (audioType._Equal("MP4"))
		{
			advancedMediaPlayer->playMp4(filename);
		}
		else if(audioType._Equal("VLC"))
		{
			advancedMediaPlayer->playVlc(filename);
		}
	}

private:
	
	AdvancedMediaPlayer * advancedMediaPlayer;
};

class AudioPlayer : public MediaPlayer {
public:
	void play(string audioType, string filename) {
		if (audioType._Equal("MP3"))
		{
			std::cout << "play MP3: " << filename.data() << std::endl;
		}
		else if(audioType._Equal("MP4") || audioType._Equal("VLC"))
		{
			mediaAdapter = new MediaAdapter(audioType);
			mediaAdapter->play(audioType, filename);
		}
		else
		{
			std::cout << "Invalid media. " << audioType.data() << " format not supported" << std::endl;
		}
	}
private:
	MediaAdapter * mediaAdapter;
};