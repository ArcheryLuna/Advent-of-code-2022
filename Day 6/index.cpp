#include <iostream>
#include <iomanip> // E.g., std::quoted
#include <string>
#include <sstream> // E.g., std::istringstream, std::ostringstream
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <deque>
#include <array>
#include <ranges> // E.g., std::subrange, std::view 
#include <utility> // E.g., std::pair,..
#include <algorithm> // E.g., std::find, std::all_of,...
#include <numeric> // E.g., std::accumulate
#include <limits> // E.g., std::numeric_limits
#include <optional> // E.g., std::optional
#include <fstream>

using namespace std;

extern char const* pTest;
extern char const* pData;

using Result = size_t;
using Answers = std::vector<std::pair<std::string,Result>>;

using Model = std::string;

bool all_unique(auto v) {
  bool result{};
  std::cout << "\nall_unique(";
  std::set<char> detected{};
  for (auto ch : v) {
    std::cout << " " << ch;
    detected.insert(ch);
  }
  result = detected.size() == v.size();
  if (result) std::cout << ") = true";
  else std::cout << ") = false"; 
  return result;
}

namespace part1 {
  Result solve_for(char const* pData) {
      Result result{};
      std::string datastream_buffer{pData};
      std::deque<char> four_char_window{};
        std::optional<int> found_pos{};     
      for (int i=0;i<datastream_buffer.size();++i) {
        // std::cout << " for:" << i << " four_char_window.size:" << four_char_window.size();
        if (four_char_window.size()==4) four_char_window.pop_front();
        four_char_window.push_back(datastream_buffer[i]);
        if (four_char_window.size()==4 and all_unique(four_char_window)) {
          found_pos = i+1;
          break;
        }
      }
      if (found_pos) {
        result = *found_pos;
      }
      return result;
  }
}

namespace part2 {
  Result solve_for(char const* pData) {
      Result result{};
      std::string datastream_buffer{pData};
      std::deque<char> four_char_window{};
      std::optional<int> found_pos{};
      int const WINDOW_SIZE = 14;
      for (int i=0;i<datastream_buffer.size();++i) {
        // std::cout << " for:" << i << " four_char_window.size:" << four_char_window.size();
        if (four_char_window.size()==WINDOW_SIZE) four_char_window.pop_front();
        four_char_window.push_back(datastream_buffer[i]);
        if (four_char_window.size()==WINDOW_SIZE and all_unique(four_char_window)) {
          found_pos = i+1;
          break;
        }
      }
      if (found_pos) {
        result = *found_pos;
      }
      return result;
  }
}

int main(int argc, char *argv[])
{
  Answers answers{};
  answers.push_back({"Part 1 Test",part1::solve_for(pTest)});
  answers.push_back({"Part 1     ",part1::solve_for(pData)});
  answers.push_back({"Part 2 Test",part2::solve_for(pTest)});
  answers.push_back({"Part 2     ",part2::solve_for(pData)});
  for (auto const& answer : answers) {
    std::cout << "\nanswer[" << answer.first << "] " << answer.second;
  }
  // std::cout << "\nPress <enter>...";
  // std::cin.get();
  std::cout << "\n";
  return 0;
}

char const* pTest = R"(mjqjpqmgbljsphdztnvjfqwrcgsmlb)";
char const* pData = R"(bhzhtzzsczszsjjjzddfzdfzfjfzfbbnntnzznwzzvfvrrqmrmmdzzfqfhqhsqqpwpgwpppbtbnnstthmhrrsmmvsmmhjmjfmfsfjfnfnjjvcjjszjszjsszbznzbnzndzzmlldsdgdcddmqmfqqlcllbvllztzctzczdzttlmtlthtmhtmhmmszsllvzvdzzzsqzqbqccvfvcffzsfslfsllcglclwlvwvzzdsslggtzzgzdzmzddjljvvztttsgscsstztjztjztzvzwwthtftppnmpmmcpmmjlmjjjsfjsjppgcgwcggzffzwzbbmbrbprpqqpccfncfnffvcffsqqtzqzqwzwvzwwwbjbfbcbfblltnlnhhcthtvvzzfcfgfddlggbbshsggplglqqbrbggsvvzdvvlfvlvpvhhmggbrrnppjfjhffttfpffbdfbfvfqvvtcvvbvnnhbhhglgjgzzghhwrrtntrtwwfdfdmmcmtctftpptllzqllzflfrrgqgvgdvdfdbddprrrgccqvqnnmtmvmffpzzqggfbfnfwwqdqldqqlnqnttnbttrffnmmzwzjjtrjtrtmmqsmqmffqmfqfhhbthbhdhvdhvdvmvdmdhdshsqslldzztvvmzzdcccmbbhfhshrrrpsrrqqmdmmgdmmwdmdjdqqmcmttpgtgwgpwpprbrprhrsrllhsllprlplhppfzpffbhbccwdwbbrpbpvpqqmsspjssmbbmfmrmnrnwwgbwwbpwpjwwhqqgcqcvqccgffzpfftcffqlqjjznnlflhhlcczhzvhzhmzhmhfhnnqznntstwtggqjgjhggsvslltjlttfjjgffjzjwzzqzrrhlhzhbhphmhlmlzmzsmzmccvllgrrpbrbfbjfjttqjttdrdhhggqgddppqgpqgpgtptjptpllwccmwcmcpmcppdrrtstqqczqzvvlsltlddnvdvggcqqblqqsjqjttzhtzzszllqsqfqddqdbqddwqddfzzlczcscfsfpfdpdrpddsggcqchcfcpcssstwstwtggghvhqhzzqssjddwjwbjjsnjnfnwwglwwfnfhnnscsggzgjzzhzmmqfqsqwqrwqqqdtdcttzvvnbngbbcdbdggddnmddgzghhzgghwwbjbttlwlcctlccwwdhhrqrvrjjlglssgttpllwclwwtptwptwtvthtbhbzhbzhhrsrwwwnrwrfwfnwnhhnqqdjqjpqqwdwttzhttcdttvztzltzlzmzddrsdsfdsfftdfffmwffrjrffqrfqfsfqqqgqjggwzzrnnqfnqffdbfbtbbrpbrpbptpwttjmjjzrrhhqppdzdtdjttqwwtddjdzzmgzzhwwwdsdgssprsrgsgbbphhdpdwppnfppdqqwzzpbzzqwqpqsqhqdhqqtwwjnnmvmwvmmwwgjgzjjvcjcvcjcnjcncmmphmmvmwmwpwbbtbffhnhshgssgvgvrrbwbtbddqmqfqvvfqvqdvvdbvdbdcdfdlflmffrwwgmmttrztrrfrqrpqrrzjrjpjdpjprrnhhbhcbbcwwqlwwcssbddfrfjrfjfrjfjvvdmdtdzzlvzlzhzmhmhphchnnfqnffvccfpfbfpfqpprrmttzrzzjzmjmzjmmfvmmrzrqqdllgjlglcchssgllsbllrbrlrjlrrhhfwwsqwsstpssznzcznzqzssvtvtrrqwqvvtssgfsfhssljjnwjnjddjdggclcrrfsfhsstgtdtctfttvvsbvvbtbttcgcssjlslhlpljpppwzwnwdnngmgjjbzznwwdllrrfppshhvdhhldhdbbdbjbdjjrnjjzhzfhhsqqbqgmsbvnjsptlrsszlqfmgprvscphmqztbgtlrqvcgdzcptcqjncrdtfqnghnbmwwmcjgtjlbvqqzslgbbntrdfnvfjvfgcgngndjcspgwmpnsrqzzvzljbzlzzrwflrqqqmhsvqwbmdftnhwwzgqrlhddbbtwvbphljmstcjzvpjqwcnhlvpqvqdgvntgqzqwrlwbwvngwtqgrhznlzcvbwqmwncccjctrdzrmzjsvrmcfpjjcczhbvdfwhqvczggfmrspvprvvthvtqnsphpcsdmbrtbdqljvssdrhwjsrrlzprstpgqcbpmnpdgzgjttwcfrgjnsghmszlclgvmlsjrqfvflbnhwwphtvrnrbhdvdglcvgpzfsjpwwhtlvvdzthsrldfzhnlrblzsjjnwclqsqzgdbflhvpwcrtfbfbjcjttbjpvfgvfcswnqqwshbmqlscdzzwshfqwsvwnwzltbnrmzzhzvtwpzqcgwshpvzgtcmwrtrwctnpzbznnwqphnrgwljtrcwlqmvlndwrdrctztnmswslqmbjcmtlrmcpjvzccqszrnflqnqzttbhqlrhbmqdpscqvfgtdbnwjdcljwcbgbgjfzgrgpwqzqgbnrtpntfthhdbqmswvhnmwmszpghgjjzrbnbbfjblpstdfslmmmqfdcrhblqjqfphnldrvvfpnfrcvprjnqbzbspfpjtgqhnjbhnrwzcjvdbshhqpgrmzqpmjfmqwqvvdbddbsldwzzsrhnhsjjnvljrbwcnjrnjpmrrvfthftgptgtlpbgqffthflgftwcrqcqwqwrmrcmfrcqgmrnqjbscdcgrqlhjzthvzdgjbvpswflqcgsnlmgmvcsttsgmnqdtvwdvrndvfdcvrcwmqlmlhtrvthsndsrmnsfmdmfnpfmfhzjqmtcjzcrnsjdztztvgdtlrmbdmmstbfgpmmzthcslpvgrpgfljfgqlqhldfwvvvdvbzjtdtppbtrnqwsqztjrsjhtfrgmvsdngvsdzjgpwrldqpzdpvhljzpjvttwltdwcrhcbrgrvdrmpwvdwjchqsjfprbgtjtzggvgrgmlvvwqrjfprbbgjjqrtdfnrdffwbswbvqtqtfsrhsgrjhftqldhmcnmsnfflmdrzqdjmbqqgqsttdmtrrvfsjnccnhcpcvqtrzdjzrpwswmjvvgsgwvnmdgqwlctrlhqnsmczbwsjhmtgvdcgsndzlstcwchcztqqbtdwfvlljdvdlzljslgnzpmqvzfcvqhdzvgchffqgfwrnmwqzwgbzblpmvddlvnhglrhdnwzqwztzgjczjpwcjwmpnrnrhncfjfggrbphrjztwtfqmfjlwfhnqfftfghbnvtwgtmdzzrdrtmfrwhrrbhzmcllsgqzwzzqtgdggvzptvtdcpzmtmsfcfbjtzlbdrwhdbtdhhrgggmddnzsvjwgcdcqfppqwphfvlhmgqsznlhmgpnjvcvrwwppnphchgsrhjwjcpjggsrcwrvnllfgrmjltfzwhmbqwpwwzmrtlqcprrqztcgnghcbvzrbfptjmhtdcfhhffdbrswqpnpppnpqwtflrrmqgjzctmmvvvwzllbsfdvpqjtmvpjcpmjztscsgbdznfgcmtjzdqzwqrsvstnnvddcstzqjtnbsnlptpmbmfqmhppgnjrffqrtchgptbmwlwbwbcqqfngpbwtwdmlmdstmqwcwjtbwbbbhghgptmvhfmvqfvpwqzwnbjdhpwlgjgvprdjbnlzhnllssbpvzfzspwsscfpqtpdvtzvqncfrfrgddsdglqvpblmpcczlqfdmwzmgvrljhqtcglcvfhbdwhbttqqrjbqwhsrhrbjwmtqwqddvdggdwfsmnpbpvvgsqnvvrqntwmbzdnqpmmqtbnlsbmslpfmqjtgvbddhwvlvjtlrhqdpfnjwtbhwjwdrpgctbbrdqvbbnvgqwngrhqfvwzmlqtmhfqphnmczlbdpnbmpvwrsjbcnjnvcfgnsvlhpzdgdzgvfbgwdcrswznrggnghzssdwqvvlwftqhbnwdvghhvjlqqmcnqmvbwhrrnsswlwmwbsmpcpdzzgmcmqnzpvjpzqbwcsgdhqtqhcpbtqftvscmntsbdcbrndvlfhprpblzbjcpqhfljtvnvtgvrcgqbsgl)";