import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.charset.Charset;
import java.util.Date;

import org.apache.mina.core.service.IoAcceptor;
import org.apache.mina.core.service.IoHandlerAdapter;
import org.apache.mina.core.session.IdleStatus;
import org.apache.mina.core.session.IoSession;
import org.apache.mina.filter.codec.ProtocolCodecFilter;
import org.apache.mina.filter.codec.textline.TextLineCodecFactory;
import org.apache.mina.filter.logging.LoggingFilter;
import org.apache.mina.transport.socket.nio.NioSocketAcceptor;

public class MinaTimeServer {
	private static final int PORT = 9999;

	public static void main(String[] args) {
		System.out.println("mina ...");
		IoAcceptor acceptor = new NioSocketAcceptor();
		acceptor.getFilterChain().addLast("logger", new LoggingFilter());
		acceptor.getFilterChain().addLast(
				"codec",
				new ProtocolCodecFilter(new TextLineCodecFactory(Charset
						.forName("UTF-8"))));
		acceptor.setHandler(new TimeServerHandler()); // 設定read緩衝區和空閒時間
		acceptor.getSessionConfig().setReadBufferSize(2048);
		acceptor.getSessionConfig().setIdleTime(IdleStatus.BOTH_IDLE, 10); // 綁定連接埠
		try {
			acceptor.bind(new InetSocketAddress(PORT));
		} catch (IOException e) { // TODO Auto-generatedcatch block
			e.printStackTrace();
		}
	}
}

class TimeServerHandler extends IoHandlerAdapter {
	@Override
	public void exceptionCaught(IoSession session, Throwable cause)
			throws Exception { // TODO Auto-generated method stub
		super.exceptionCaught(session, cause);
		cause.getStackTrace();
	}

	@Override
	public void messageReceived(IoSession session, Object message)
			throws Exception { // TODO Auto-generated method stub
		String str = message.toString();
		if (str.trim().equalsIgnoreCase("quit")) {
			session.close(true);
			return;
		}
		Date date = new Date();
		session.write(date.toString());
		System.out.println("Message written...");
	}

	@Override
	public void sessionIdle(IoSession session, IdleStatus status)
			throws Exception { // TODO Auto-generated method stub
		System.out.println("IDLE:" + session.getIdleCount(status));
	}
}
