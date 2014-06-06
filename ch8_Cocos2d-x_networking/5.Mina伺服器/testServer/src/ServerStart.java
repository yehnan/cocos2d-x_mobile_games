import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.charset.Charset;

import org.apache.mina.core.service.IoAcceptor;
import org.apache.mina.filter.codec.ProtocolCodecFilter;
import org.apache.mina.filter.codec.textline.TextLineCodecFactory;
import org.apache.mina.filter.logging.LoggingFilter;
import org.apache.mina.transport.socket.nio.NioSocketAcceptor;



public class ServerStart {
	public static final int PORT=9123;
	
	/**
	 * @param args
	 */
	public static void main(String[] args) throws IOException{
		// TODO Auto-generated method stub
		//IO Service 分Acceptor和Connector 
		IoAcceptor acceptor=new NioSocketAcceptor();
		//得到過濾器鏈 加入日誌處理與 解碼
		acceptor.getFilterChain().addLast("logger", new LoggingFilter());
		acceptor.getFilterChain().addLast("codec", new ProtocolCodecFilter(new TextLineCodecFactory(Charset.forName("UTF-8"))));
		//設定處理器
		acceptor.setHandler(new Test());
		//設定本地監聽位址
		acceptor.setDefaultLocalAddress(new InetSocketAddress(PORT));
		acceptor.bind(); //綁定位址
	}

}
