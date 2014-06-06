

import java.text.DateFormat;
import java.util.Date;

import org.apache.mina.core.service.IoHandlerAdapter;
import org.apache.mina.core.session.IoSession;

//�Լ����x��I/O̎����
public class Test extends IoHandlerAdapter{
	@Override
	public void messageReceived(IoSession session, Object message)
			throws Exception {
		// TODO Auto-generated method stub
		super.messageReceived(session, message);
		String str=message.toString();
		Date data=new Date();
		DateFormat d=DateFormat.getDateInstance();
		String strDate=d.format(data);
		session.write(str);
		System.out.println("�յ��ͻ��˰l���ӍϢ��"+str+" "+strDate);
	}

	@Override
	public void sessionCreated(IoSession session) throws Exception {
		// TODO Auto-generated method stub
		super.sessionCreated(session);
		//ip address
		System.out.println("IP:"+session.getRemoteAddress().toString());
	}
	
}
